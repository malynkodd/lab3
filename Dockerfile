FROM alpine AS build
RUN apk add --no-cache git build-base cmake automake autoconf coreutils
WORKDIR /home/optima
RUN git clone https://github.com/malynkodd/lab3.git .
RUN autoreconf -i
RUN ./configure
RUN make

FROM alpine
RUN apk add --no-cache libstdc++
COPY --from=build /home/optima/my_program /usr/local/bin/my_program
ENTRYPOINT ["/usr/local/bin/my_program"]

