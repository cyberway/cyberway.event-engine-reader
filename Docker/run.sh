#!/bin/bash

docker volume create cyberway-queue || true
docker-compose up -d
