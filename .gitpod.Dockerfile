
FROM archlinux:latest

RUN pacman -Sy --noconfirm \
          base-devel \
          clang-tools-extra \
          cmake \
          gdb \
          git \
          ninja
