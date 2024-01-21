PARENT_DIR := /home/hiroakik4/42/
SRCS := main.cpp glad.c Shader.cpp Parser.cpp
INCLUDE := -I../glm -I../glad/include -I../glfw/include -I.
LDFLAGS := -L$(PARENT_DIR)scop/glfw/build/src `pkg-config --libs glfw3` -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
NAME := scop
CXX := g++

all: $(NAME)

$(NAME):
	$(CXX) $(SRCS) $(INCLUDE) $(LDFLAGS) -o $(NAME)

clean:
	rm -rf $(NAME)

re: clean all

.PHONY: all clean re
