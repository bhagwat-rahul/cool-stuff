package mandelbrot
import "core:fmt"
import "core:os"
import "core:strconv"
import "core:strings"

main :: proc() {
	program_path: string
	width, height, max_iterations: int
	min_real, max_real, min_image, max_image: f64
	// Get user input here for params
	if len(os.args) < 8 {
		fmt.println("You are missing some args")
	} else {
		parse_passed: bool
		program_path = os.args[0]
		width, parse_passed = strconv.parse_int(os.args[1])
		if !parse_passed {
			fmt.println("invalid input for width")
			return
		}
		height, parse_passed = strconv.parse_int(os.args[2])
		if !parse_passed {
			fmt.println("invalid input for height")
			return
		}
		max_iterations, parse_passed = strconv.parse_int(os.args[3])
		if !parse_passed {
			fmt.println("invalid input for max_iteration")
			return
		}
		min_real, parse_passed = strconv.parse_f64(os.args[4])
		if !parse_passed {
			fmt.println("invalid input for min_real")
			return
		}
		max_real, parse_passed = strconv.parse_f64(os.args[5])
		if !parse_passed {
			fmt.println("invalid input for max_real")
			return
		}
		min_image, parse_passed = strconv.parse_f64(os.args[6])
		if !parse_passed {
			fmt.println("invalid input for min_image")
			return
		}
		max_image, parse_passed = strconv.parse_f64(os.args[7])
		if !parse_passed {
			fmt.println("invalid input for max_image")
			return
		}
	}
	mandelbrot_image_file_path, image_made := draw_mandelbrot(
		width,
		height,
		max_iterations,
		min_real,
		max_real,
		min_image,
		max_image,
		program_path,
	)
	if (image_made) {
		fmt.println("Created image path", mandelbrot_image_file_path)
	} else {
		fmt.println("Error creating mandelbrot image")
	}
}

draw_mandelbrot :: proc(
	width, height, max_iterations: int,
	min_real, max_real, min_image, max_image: f64,
	pwd: string,
) -> (
	file_path: string = "",
	image_made: bool = true,
) {
	file_path = strings.concatenate({pwd, "/", "mandelbrot.ppm"})

	for i: int = 0; i < height - 1; i += 1 {
		for j: int = 0; j < width - 1; j += 1 {
			fmt.print(".")
		}
		fmt.println()
	}

	return
}
