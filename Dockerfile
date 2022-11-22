FROM ubuntu

RUN apt update &&\ 
    apt upgrade 
RUN apt install -y build-essential gdb software-properties-common lsb-release &&\
    apt clean all

# Set up kitware for cmake
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null &&\
    apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"

RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 6AF7F09730B3F0A4 &&\
    apt update &&\
    apt install -y kitware-archive-keyring &&\ 
    rm /etc/apt/trusted.gpg.d/kitware.gpg 
    
RUN apt update &&\ 
    apt install -y cmake

RUN apt install -y libglew-dev freeglut3-dev libglfw3-dev libglfw3 libglm-dev pkg-config

ENV DISPLAY 172.18.48.1:0.0

# Build App
RUN mkdir -p /home/root/SolarSystem
WORKDIR /home/root/SolarSystem
COPY . .
RUN mkdir build
WORKDIR build
RUN cmake .. && make
WORKDIR ..

CMD ./build/SolarSystem