FROM ubuntu:16.04
RUN apt-get -y -qq update
RUN apt-get -y -qq upgrade
RUN apt-get install -y \
            gcc-5-base\
            libgcc-5-dev\
            g++\
            cmake\
            doxygen\
            git
RUN apt-get install -y \
            libeigen3-dev\
            libqt5opengl5-dev
WORKDIR /home
RUN git clone https://github.com/Ethiy/imagine-pp.git
WORKDIR imagine-pp/
RUN mkdir build && mkdir build/xenial
WORKDIR build/xenial
RUN cmake ../..
RUN make -j4