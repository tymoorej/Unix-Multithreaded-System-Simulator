a4tasks: includes.hpp a4tasks.cpp task.cpp task.hpp resources.hpp resources.cpp shared.hpp shared.cpp monitor.hpp monitor.cpp
	g++ shared.cpp task.cpp resources.cpp a4tasks.cpp monitor.cpp -o a4tasks

clean:
	rm -rf *.o -f; rm -rf .vscode -f

tar:
	tar -cvf submit.tar ./ --exclude .git

end:
	pkill -U $$USER