ARG buildtype=stable
FROM cyberway/builder:$buildtype as builder

ARG branch=master
ARG compiletype=RelWithDebInfo
ARG ref=heads/$branch

ADD https://api.github.com/repos/cyberway/cyberway.event-engine-reader/git/refs/$ref /etc/version.json

RUN cd /opt && git clone -b $branch https://github.com/cyberway/cyberway.event-engine-reader.git --recursive

RUN cd /opt/cyberway.event-engine-reader && mkdir build && cd build \
    && echo "$branch:$(git rev-parse HEAD)" > /etc/cyberway.event-engine-reader.version \
    && cmake \
        -DCMAKE_BUILD_TYPE=$compiletype \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_CXX_COMPILER=clang++ \
        .. \
    && make

FROM ubuntu:18.04

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get -y install openssl ca-certificates \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /opt/cyberway.event-engine-reader/build/cyberway.event-engine-reader /opt/cyberway/bin/cyberway.event-engine-reader
COPY --from=builder /etc/version.json /opt/cyberway/cyberway.event-engine-reader.version

RUN ldconfig

VOLUME /queue
WORKDIR /opt

