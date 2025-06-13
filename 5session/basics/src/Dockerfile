FROM debian:bullseye

RUN apt-get update && apt-get install -y g++ make curl

COPY . /app
WORKDIR /app

RUN g++ main.cpp -o cookie_demo_cpp -std=c++17 -lpthread

EXPOSE 8080
CMD ["./cookie_demo_cpp"]
