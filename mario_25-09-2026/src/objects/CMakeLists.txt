target_sources(${PROJECT_NAME}
	PRIVATE
		full_box.cpp
		mario.cpp
		money.cpp
		mushroom.cpp
		mushroom_box.cpp
		w_enemy.cpp
		f_enemy.cpp
		j_enemy.cpp
		moving_platform.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
