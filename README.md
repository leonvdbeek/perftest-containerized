# perftest-containerized
A containerized version of perftest from: http://eggdrop.ch/projects/perftest/

To run image: 
`docker run -it --rm --name perftest leonvdbeek/perftest`
This will output the details of the run directly in the terminal because of the `-it` tag, and remove the container afterwards because of the `--rm` tag.

To build image:
1. Clone this repo
2. Change whatever you desire
3. Build image using: `sudo docker build -t leonvdbeek/perftest .`

To run standalone (not within a container):
1. Clone this repo
2. Run: `make`
3. Run: `./perftest`

Link to [DockerHub](https://hub.docker.com/repository/docker/leonvdbeek/perftest)