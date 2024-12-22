FROM alpine AS build
RUN apk add --no-cache git build-base cmake automake autoconf coreutils
WORKDIR /home/optima

COPY . /home/optima 


RUN autoreconf -i
RUN ./configure
RUN make


FROM alpine
RUN apk add --no-cache libstdc++


COPY --from=build /home/optima/my_program /usr/local/bin/my_program


RUN chmod +x /usr/local/bin/my_program


ENTRYPOINT ["/usr/local/bin/my_program"]

