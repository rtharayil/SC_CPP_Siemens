 docker build -t cpp-csrf-session .
 docker run -p 80XX:8080 cpp-csrf-session

 docker stop $(docker ps -q)
