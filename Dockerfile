FROM alpine:latest
RUN apk add build-base
COPY . /usr/src/perftest
WORKDIR /usr/src/perftest
RUN gcc -lpthread -pthread -o perftest *.c
CMD ["./perftest"]
