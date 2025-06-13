 docker build -t cookie_demo .
 docker run -p 80XX:8080 cookie_demo

 docker stop $(docker ps -q)
