#include <spdlog/spdlog.h>

namespace engine
{
	class fps {
	public:
		fps(int display_interval_sec = 5) : 
			display_interval(display_interval_sec),
			frame_count(0),
			last_display_time(std::chrono::steady_clock::now()),
			start_time(std::chrono::steady_clock::now()) 
		{}

		void frame() {
			frame_count++;
			auto now = std::chrono::steady_clock::now();

			if (std::chrono::duration_cast<std::chrono::seconds>(now - last_display_time).count() >= display_interval) 
			{
				double elapsed_secs = 
					std::chrono::duration_cast<std::chrono::duration<double>>(now - start_time).count();
				int fps = static_cast<int>(std::round(frame_count / elapsed_secs));

				spdlog::info("fps: {}", fps);

				last_display_time = now;
				frame_count = 0;
				start_time = now;
			}
		}

	private:
		int display_interval;
		int frame_count;
		std::chrono::steady_clock::time_point last_display_time;
		std::chrono::steady_clock::time_point start_time;
	};
}