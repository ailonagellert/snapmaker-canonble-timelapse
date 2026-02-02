# Dockerfile
FROM python:3.11-slim
WORKDIR /app
COPY timelapse_monitor_docker.py /app/monitor.py
RUN apt-get update && apt-get install -y openssh-client && rm -rf /var/lib/apt/lists/*
CMD ["python", "monitor.py"]