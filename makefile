# dir vars
INC = inc/
SRC = src/
TEST_SRC = test_src/
OBJ = obj/
BIN = bin/
LIB = lib/
GTEST = gtest-1.6.0/

#testing vars

OBJS = $(OBJ)main.o \
	$(OBJ)byu_gl.o \
	$(OBJ)matrix.o \
	$(OBJ)vector.o \
	$(OBJ)vector4f.o \
	$(OBJ)matrix4f.o \
	$(OBJ)vertex.o \
	$(OBJ)square_matrix_stack.o \
	$(OBJ)matrix4f_stack.o \
	$(OBJ)raster.o \
	$(OBJ)geometry_pipeline.o \
	$(OBJ)draw_command.o \
	$(OBJ)draw_points.o \
	$(OBJ)draw_smooth_point.o \
	$(OBJ)draw_bresenham_line.o \
	$(OBJ)draw_bres_line.o \
	$(OBJ)draw_dda_line.o \
	$(OBJ)draw_line_strip.o \
	$(OBJ)draw_line_loop.o \
	$(OBJ)draw_bres_edge.o \
	$(OBJ)draw_triangle.o \
	$(OBJ)draw_triangles.o \
	$(OBJ)draw_triangle_strip.o \
	$(OBJ)draw_triangle_fan.o \
	$(OBJ)draw_quads.o \
	$(OBJ)draw_quad_strip.o \
	$(OBJ)graphics_state.o \
	$(OBJ)vertex_buffer.o \
	$(OBJ)draw_black_white_gradient.o \
	$(OBJ)draw_command_factory.o \
	$(OBJ)blending_func.o \
	$(OBJ)scenes.o \
	$(OBJ)matrix_state.o \
	$(OBJ)plane_depth_calculator.o\
	$(OBJ)line_depth_calculator.o \
	$(OBJ)ray_tracer.o \
	$(OBJ)eye.o \
	$(OBJ)math_utils.o \
	$(OBJ)screen.o \
	$(OBJ)screen_raster.o \
	$(OBJ)ray.o \
	$(OBJ)illuminated_object.o \
	$(OBJ)sphere.o \
	$(OBJ)lambert_light.o \
	$(OBJ)scene.o \
	$(OBJ)light_ray.o\
	$(OBJ)camera.o\
	$(OBJ)plane.o \
	$(OBJ)rtriangle.o

RTOBJS = $(OBJ)main.o \
	$(OBJ)ray_tracer.o\
	$(OBJ)eye.o\
	$(OBJ)screen.o\
	$(OBJ)ray.o\
	$(OBJ)illuminated_object.o\
	$(OBJ)math_utils.o\
	$(OBJ)sphere.o\
	$(OBJ)lambert_light.o\
	$(OBJ)scene.o\
	$(OBJ)light_ray.o\
	$(OBJ)camera.o\
	$(OBJ)plane.o\
	$(OBJ)rtriangle.o\
	$(OBJ)matrix.o \
	$(OBJ)vector.o \
	$(OBJ)vector4f.o \
	$(OBJ)matrix4f.o \
	$(OBJ)vertex.o \
	$(OBJ)square_matrix_stack.o \
	$(OBJ)matrix4f_stack.o \
	$(OBJ)plane_depth_calculator.o \
	$(OBJ)screen_raster.o 

# main program

gl: $(RTOBJS) 
	g++ -o $(BIN)gl $(RTOBJS) -lglut -lGLU -lGL -lGLEW

$(OBJ)main.o: $(SRC)main.cpp $(INC)matrix.h
	g++ -c -g -o $(OBJ)main.o -I$(INC) $(SRC)main.cpp

# ray tracing algorithm

$(OBJ)ray_tracer.o: $(SRC)ray_tracer.cpp $(INC)ray_tracer.h
	g++ -c -g -o $(OBJ)ray_tracer.o -I$(INC) $(SRC)ray_tracer.cpp

$(OBJ)eye.o: $(SRC)eye.cpp $(INC)eye.h
	g++ -c -g -o $(OBJ)eye.o -I$(INC) $(SRC)eye.cpp

$(OBJ)screen.o: $(SRC)screen.cpp $(INC)screen.h
	g++ -c -g -o $(OBJ)screen.o -I$(INC) $(SRC)screen.cpp

$(OBJ)ray.o: $(SRC)ray.cpp $(INC)ray.h
	g++ -c -g -o $(OBJ)ray.o -I$(INC) $(SRC)ray.cpp

$(OBJ)illuminated_object.o: $(SRC)illuminated_object.cpp $(INC)illuminated_object.h
	g++ -c -g -o $(OBJ)illuminated_object.o -I$(INC) $(SRC)illuminated_object.cpp

$(OBJ)math_utils.o: $(SRC)math_utils.cpp $(INC)math_utils.h
	g++ -c -g -o $(OBJ)math_utils.o -I$(INC) $(SRC)math_utils.cpp

$(OBJ)sphere.o: $(SRC)sphere.cpp $(INC)sphere.h
	g++ -c -g -o $(OBJ)sphere.o -I$(INC) $(SRC)sphere.cpp

$(OBJ)lambert_light.o: $(SRC)lambert_light.cpp $(INC)lambert_light.h
	g++ -c -g -o $(OBJ)lambert_light.o -I$(INC) $(SRC)lambert_light.cpp

$(OBJ)scene.o: $(SRC)scene.cpp $(INC)scene.h
	g++ -c -g -o $(OBJ)scene.o -I$(INC) $(SRC)scene.cpp

$(OBJ)light_ray.o: $(SRC)light_ray.cpp $(INC)light_ray.h
	g++ -c -g -o $(OBJ)light_ray.o -I$(INC) $(SRC)light_ray.cpp

$(OBJ)camera.o: $(SRC)camera.cpp $(INC)camera.h
	g++ -c -g -o $(OBJ)camera.o -I$(INC) $(SRC)camera.cpp

$(OBJ)plane.o: $(SRC)plane.cpp $(INC)plane.h
	g++ -c -g -o $(OBJ)plane.o -I$(INC) $(SRC)plane.cpp

$(OBJ)rtriangle.o: $(SRC)rtriangle.cpp $(INC)rtriangle.h
	g++ -c -g -o $(OBJ)rtriangle.o -I$(INC) $(SRC)rtriangle.cpp

$(OBJ)vector.o: $(SRC)vector.cpp $(INC)vector.h
	g++ -c -g -o $(OBJ)vector.o -I$(INC) $(SRC)vector.cpp

$(OBJ)gl.o: $(SRC)byu_gl.cpp $(INC)byu_gl.h
	g++ -c -g -o $(OBJ)gl.o -I$(INC) $(SRC)byu_gl.cpp

$(OBJ)matrix.o: $(SRC)matrix.cpp $(INC)matrix.h
	g++ -c -g -o $(OBJ)matrix.o -I$(INC) $(SRC)matrix.cpp

$(OBJ)vector4f.o: $(SRC)vector4f.cpp $(INC)vector4f.h $(INC)vector.h
	g++ -c -g -o $(OBJ)vector4f.o -I$(INC) $(SRC)vector4f.cpp

$(OBJ)matrix4f.o: $(SRC)matrix4f.cpp $(INC)matrix4f.h
	g++ -c -g -o $(OBJ)matrix4f.o -I$(INC) $(SRC)matrix4f.cpp

$(OBJ)vertex.o: $(SRC)vertex.cpp $(INC)vertex.h
	g++ -c -g -o $(OBJ)vertex.o -I$(INC) $(SRC)vertex.cpp

$(OBJ)square_matrix_stack.o: $(SRC)square_matrix_stack.cpp $(INC)square_matrix_stack.h $(INC)matrix.h
	g++ -c -g -o $(OBJ)square_matrix_stack.o -I$(INC) $(SRC)square_matrix_stack.cpp

$(OBJ)matrix4f_stack.o: $(SRC)matrix4f_stack.cpp $(INC)matrix4f_stack.h $(INC)matrix.h
	g++ -c -g -o $(OBJ)matrix4f_stack.o -I$(INC) $(SRC)matrix4f_stack.cpp

$(OBJ)raster.o: $(SRC)raster.cpp $(INC)raster.h
	g++ -c -g -o $(OBJ)raster.o -I$(INC) $(SRC)raster.cpp

$(OBJ)screen_raster.o: $(SRC)screen_raster.cpp $(INC)screen_raster.h
	g++ -c -g -o $(OBJ)screen_raster.o -I$(INC) $(SRC)screen_raster.cpp

$(OBJ)plane_depth_calculator.o: $(SRC)plane_depth_calculator.cpp $(INC)plane_depth_calculator.h
	g++ -c -g -o $(OBJ)plane_depth_calculator.o -I$(INC) $(SRC)plane_depth_calculator.cpp

# unit tests
#./$(BIN)test-main \

test: vector-test matrix-test vector4f-test matrix4f-test matrix4f-stack-test
	./$(BIN)vector-test --log_level=test_suite; \
	./$(BIN)matrix-test --log_level=test_suite; \
	./$(BIN)vector4f-test --log_level=test_suite; \
	./$(BIN)matrix4f-test --log_level=test_suite; \
	./$(BIN)matrix4f-stack-test --log_level=test_suite; \


vector-test: $(OBJS) $(OBJ)vector-test.o $(OBJ)vector.o
	g++ -o $(BIN)vector-test $(OBJ)vector-test.o $(OBJ)vector.o
	
$(OBJ)vector-test.o: $(TEST_SRC)vector-test.cpp 
	g++ -c -g -o $(OBJ)vector-test.o -I$(INC) $(TEST_SRC)vector-test.cpp -lboost_unit_test_framework

matrix-test: $(OBJS) $(OBJ)matrix-test.o $(OBJ)matrix.o $(OBJ)vector.o
	g++ -o $(BIN)matrix-test $(OBJ)matrix-test.o $(OBJ)matrix.o $(OBJ)vector.o
	
$(OBJ)matrix-test.o: $(TEST_SRC)matrix-test.cpp 
	g++ -c -g -o $(OBJ)matrix-test.o -I$(INC) $(TEST_SRC)matrix-test.cpp -lboost_unit_test_framework
	
vector4f-test: $(OBJS) $(OBJ)vector4f-test.o $(OBJ)vector4f.o
	g++ -o $(BIN)vector4f-test $(OBJ)vector4f-test.o $(OBJ)vector4f.o $(OBJ)vector.o
	
$(OBJ)vector4f-test.o: $(TEST_SRC)vector4f-test.cpp $(OBJ)vector.o
	g++ -c -g -o $(OBJ)vector4f-test.o -I$(INC) $(TEST_SRC)vector4f-test.cpp -lboost_unit_test_framework

matrix4f-test: $(OBJS) $(OBJ)matrix4f-test.o $(OBJ)matrix4f.o $(OBJ)vector4f.o $(OBJ)vector.o
	g++ -o $(BIN)matrix4f-test $(OBJ)matrix4f-test.o $(OBJ)matrix4f.o $(OBJ)matrix.o $(OBJ)vector4f.o $(OBJ)vector.o
	
$(OBJ)matrix4f-test.o: $(TEST_SRC)matrix4f-test.cpp $(OBJ)matrix.o
	g++ -c -g -o $(OBJ)matrix4f-test.o -I$(INC) $(TEST_SRC)matrix4f-test.cpp -lboost_unit_test_framework

matrix4f-stack-test: $(OBJS) $(OBJ)matrix4f-stack-test.o $(OBJ)matrix4f.o $(OBJ)vector4f.o $(OBJ)vector.o
	g++ -o $(BIN)matrix4f-stack-test $(OBJ)matrix4f-stack-test.o $(OBJ)matrix4f_stack.o \
	$(OBJ)matrix4f.o $(OBJ)matrix.o $(OBJ)vector4f.o $(OBJ)vector.o
	
$(OBJ)matrix4f-stack-test.o: $(TEST_SRC)matrix4f-stack-test.cpp $(OBJ)matrix4f.o
	g++ -c -g -o $(OBJ)matrix4f-stack-test.o -I$(INC) $(TEST_SRC)matrix4f-stack-test.cpp -lboost_unit_test_framework

# build the library

# utility commands

clean:
	rm $(OBJ)*.o; \
	rm $(BIN)*

run:
	./$(BIN)gl

mem-test:
	valgrind $(BIN)gl
