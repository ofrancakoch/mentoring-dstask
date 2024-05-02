FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY ./main.c /app

RUN gcc -o taskmanager main.c

CMD ["./taskmanager"]
