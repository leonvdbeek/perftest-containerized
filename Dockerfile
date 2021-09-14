FROM gcc:4.9
COPY . /usr/src/perftest
WORKDIR /usr/src/perftest
RUN gcc -lpthread -pthread -o perftest *.c
CMD ["./perftest"]
