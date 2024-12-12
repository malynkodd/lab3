FROM alpine
WORKDIR /home/optima
COPY ../my_program .
RUN apk add libstdc++
RUN apk add libc6-compat
ENTRYPOINT ["./my_program"]
