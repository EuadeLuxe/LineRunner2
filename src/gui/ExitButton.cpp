#include "ExitButton.h"

void ExitButton::call(const std::shared_ptr<bb::Entity> entity){
	glutLeaveMainLoop();
}
