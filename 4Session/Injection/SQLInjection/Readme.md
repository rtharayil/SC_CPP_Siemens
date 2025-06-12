# Build docker image
docker build -t cpp-sqli-demo .

# Run container
docker run -p 80XX:8080 cpp-sqli-demo

# Kill all containers
docker stop $(docker ps -q)
