/*
* Author: Chris Trimmer
* Assignment: Week 7 (Final Project)
* Date: 04/14/2023
*
* References:
* Ideas, structure, and support from the following sources:
*   http://www.opengl-tutorial.org/beginners-tutorials/
*   https://www.khronos.org/opengl/wiki/Getting_Started#Tutorials_and_How_To_Guides
*   https://learnopengl.com/Introduction
*   https://www.youtube.com/@snhucomputerscience
*	https://www.songho.ca/opengl/gl_cylinder.html
*/


#include <app.h>


void App::Run()
{
    if (!openWindow())
        return;

    setUpInputs();

    running = true;

    setupScene();

    while (running) {

        float currentTime = glfwGetTime();
        if (this->lastFrameTime == -1.f) {
            this->lastFrameTime = currentTime;
        }

        auto deltaTime = currentTime - this->lastFrameTime;
        this->lastFrameTime = currentTime;

        // render loop
        // -----------
        if (glfwWindowShouldClose(window)) {
            this->running = false;
            continue;
        }

        // input
        // -----
        processInput(this->window);

        update(deltaTime);

        draw();
        
    }

    glfwTerminate();

}

void App::setupScene() {


    // create the pyramid
    auto& pyr1 = projectObjects.emplace_back(std::make_unique<Pyramid>());
    //pyr1->Transform = glm::translate(pyr1->Transform, glm::vec3(0.0f, 0.0f, 0.0f));
    //pyr1->Transform = glm::scale(pyr1->Transform, glm::vec3(1.f, 1.f, 1.f));
    //pyr1->Transform = glm::rotate(pyr1->Transform, glm::radians(30.0f), glm::vec3(-1.f, 0.f, 0.f));


    auto& plane = projectObjects.emplace_back(std::make_unique<Plane>());

    auto& cylinder = projectObjects.emplace_back(std::make_unique<Cylinder>());
    auto& cylHandle = projectObjects.emplace_back(std::make_unique<Cube>());
    
    auto& smallBox = projectObjects.emplace_back(std::make_unique<SmallBox>());

    // directional - add back in when we build out separate dir light sub class
//    auto& light = projectObjects.emplace_back(std::make_unique<Light>());
    // hieght with vert and horiz rotation
//    light->Transform = glm::translate(light->Transform, glm::vec3(0.0f, 1.5f, 0.0f));
////    light->Transform = glm::translate(light->Transform, glm::vec3(0.0f, 0.5f, .5f));


    // create a point light (above pyramid)
    auto& pointLight = projectObjects.emplace_back(std::make_unique<PointLight>());
    // hieght with vert and horiz rotation
//    pointLight->Transform = glm::translate(pointLight->Transform, glm::vec3(1.0f, 1.0f, -0.3f));
    pointLight->Transform = glm::translate(pointLight->Transform, glm::vec3(0.0f, 1.4f, 0.0f));

    auto* castLight = reinterpret_cast<PointLight*>(pointLight.get());
    //castLight->AmbientColor = { 0.1f, 0.1f, 0.1f }; // change colors here
    //castLight->DiffuseColor = { 0.9f, 1.f, 0.7f };  // make diff brighter than amb
    //castLight->SpecColor = { 0.9f, 1.f, 0.7f };  // make spec brighter than amb

    castLight->AmbientColor = { 0.5f, 0.2f, 1.0f }; // change colors here
    castLight->DiffuseColor = { 0.5f, 0.2f, 1.0f };  // make diff brighter than amb
    castLight->SpecColor = { 0.1f, 0.1f, 0.1f };  // make spec brighter than amb


    // set constants
    castLight->ConstantVar = 1.f; // should always be 1
    castLight->LinearVar = 0.35f; 
    castLight->QuadVar = 0.44f;

      
    // add another point light (above box)
    auto& pointLight2 = projectObjects.emplace_back(std::make_unique<PointLight>());
    // hieght with vert and horiz rotation
//    pointLight2->Transform = glm::translate(pointLight2->Transform, glm::vec3(1.0f, 0.6f, -0.3f));
//    pointLight2->Transform = glm::translate(pointLight2->Transform, glm::vec3(0.0f, 1.4f, 1.8f));
    pointLight2->Transform = glm::translate(pointLight2->Transform, glm::vec3(0.1f, 0.0f, 1.4f));

    auto* castLight2 = reinterpret_cast<PointLight*>(pointLight2.get());
    //castLight2->AmbientColor = { 1.0f, 0.0f, 0.0f };
    //castLight2->DiffuseColor = { 1.0f, 0.f, 0.0f };  
    //castLight2->SpecColor = { 1.0f, 0.f, 0.0f };
    castLight2->AmbientColor = { 1.0f, 1.0f, 1.0f };
    castLight2->DiffuseColor = { 0.9f, 0.f, 0.1f };
    castLight2->SpecColor = { 0.9f, 0.f, 0.1f };

    // set constants
    castLight2->ConstantVar = 1.f; // should always be 1
    castLight2->LinearVar = 0.1f;
    castLight2->QuadVar = 0.1f;



    // add another point light (near cylinder)
    auto& pointLight3 = projectObjects.emplace_back(std::make_unique<PointLight>());
    // hieght with vert and horiz rotation
    pointLight3->Transform = glm::translate(pointLight3->Transform, glm::vec3(3.0f, 1.0f, -0.3f));
//    pointLight3->Transform = glm::translate(pointLight3->Transform, glm::vec3(2.5f, 0.0f, -0.5f));

    auto* castLight3 = reinterpret_cast<PointLight*>(pointLight3.get());
    //castLight3->AmbientColor = { 1.0f, 0.0f, 0.0f };
    //castLight3->DiffuseColor = { 1.0f, 1.f, 1.0f };
    //castLight3->SpecColor = { 1.0f, 1.f, 1.0f };
    castLight3->AmbientColor = { 0.7f, 1.0f, 0.2f };
    castLight3->DiffuseColor = { 0.7f, 1.f, 0.2f };
    castLight3->SpecColor = { 0.2f, 0.2f, 0.2f };

    // set constants
    castLight3->ConstantVar = 1.f; // should always be 1
    castLight3->LinearVar = 0.51f;
    castLight3->QuadVar = 0.51f;


}



void App::update(float deltaTime)
{

    glfwPollEvents();

    handleInput(deltaTime);


    // cycle through each object and update
    for (auto& object : projectObjects) {
        object->Update(deltaTime);
    }

}

void App::draw()
{
    // change background color (.1, 0, .1, 1.0 was my first values)
    glClearColor(0.1f, 0.0f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  camera - moved to camera.cpp
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.GetProjectionMatrix();

    // add camPosition for specular
    SceneParameters sceneParameters{
        //projection,
        //view,
        //camera.GetCamPosition();
        .ProjectionMatrix = projection,
        .ViewMatrix = view,
        .CamPosition = camera.GetCamPosition(),

        // hardcoding DirectionLight (struct in types.h)
        .DirLight = {

            // make it go down x, y, front side z, axis
            // make z negative to put light on back side
            .Direction = glm::normalize(glm::vec3{ 0.0f, 0.7f, 0.5f }),
//            .Direction = glm::normalize(glm::vec3{ 0.0f, 0.9f, 0.5f }),
            //.Direction = glm::normalize(glm::vec3{-0.2f, 1.0f, 0.0f}), // raise y-axis for sun
            .AmbientColor = {0.1f, 0.1f, 0.1f}, // change colors here
          //  .AmbientColor = {1.0f, 1.0f, 1.0f},
            .DiffuseColor = {0.9f, 1.f, 0.3f},  // make diff brighter than amb
            .SpecColor = {0.9f, 1.f, 0.3f}  // make spec brighter than amb
        }
    };


    // cycle through each object and process lighting
    for (auto& model : projectObjects) {
        model.get()->ProcessLighting(sceneParameters);
    }

    // draw each object
    for (auto& model : projectObjects) {
        model.get()->Draw(sceneParameters);
        
    }


    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
}

void App::setUpInputs()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    
        auto* a = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
        
        switch (key) {
            case GLFW_KEY_ESCAPE:
                if (action == GLFW_PRESS) {
                    a->running = false;
                }
                break;

            // change view from perspective to ortho, and vice-versa
            case GLFW_KEY_P: {
                if (action == GLFW_PRESS) {
                    a->camera.SetIsPerspective(!a->camera.IsPerspective());
                }
                break;
            }

            default:
                break;

        }

    });

    glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double xpos, double ypos) {
        auto* a = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
     //   a->mousePositionCallBack(xpos, ypos);
    });

    glfwSetScrollCallback(this->window, [](GLFWwindow* window, double xOffset, double yOffset) {
    

        auto* a = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));

        //// use this to control zoom
     //// add this back after week 4
       // a->camera.IncrementZoom(yOffset * 2);


        // change mouse sensitivity/movement speed
        // this is a whack requirement - remove this after week 4
        a->ChangeSpeed();

    });


    glfwSetMouseButtonCallback(this->window, [](GLFWwindow* window, int button, int action, int mods) {
        
        // mouse does not have a repeat action, it's either pressed or released
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT: {
            if (action == GLFW_PRESS) {

            }
            else {

            }
            break;
        }
        case GLFW_MOUSE_BUTTON_RIGHT: {
            if (action == GLFW_PRESS) {

            }
            else {

            }
            break;
        }
        case GLFW_MOUSE_BUTTON_MIDDLE: {
            if (action == GLFW_PRESS) {

            }
            else {

            }
            break;
        }
        default:
            std::cout << "Unhandled mouse button event\n";
            break;
        }
    });

}

void App::handleInput(float deltaTime)
{

    //const auto deltaTime2 = 0.3f;

    auto moveAmount = this->moveSpeed * deltaTime;

    if (glfwGetKey(this->window, GLFW_KEY_W)) {
        this->camera.MoveCamera(Camera::MoveDirection::FORWARD, moveAmount);
    }

    if (glfwGetKey(this->window, GLFW_KEY_A)) {
        this->camera.MoveCamera(Camera::MoveDirection::LEFT, moveAmount);
    }

    if (glfwGetKey(this->window, GLFW_KEY_S)) {
        this->camera.MoveCamera(Camera::MoveDirection::BACKWARD, moveAmount);
    }

    if (glfwGetKey(this->window, GLFW_KEY_D)) {
        this->camera.MoveCamera(Camera::MoveDirection::RIGHT, moveAmount);
    }

    if (glfwGetKey(this->window, GLFW_KEY_Q)) {
        this->camera.MoveCamera(Camera::MoveDirection::UP, moveAmount);
    }

    if (glfwGetKey(this->window, GLFW_KEY_E)) {
        this->camera.MoveCamera(Camera::MoveDirection::DOWN, moveAmount);
    }

    double xpos, ypos;
    glfwGetCursorPos(this->window, &xpos, &ypos);
    mousePositionCallBack(xpos, ypos);

}

// change mouse sensitivity/movement speed
// this is a whack requirement - remove this after week 4
void App::ChangeSpeed() {

    if (this->cameraLookSpeed.x <= 0.2f) {
        this->cameraLookSpeed.x += 0.01f;
        this->cameraLookSpeed.y += 0.01f;
    }
    else {
        this->cameraLookSpeed.x = 0.05f;
        this->cameraLookSpeed.y = 0.05f;

    }
    std::cout << "look speed x: " << this->cameraLookSpeed.x << "\n";
    std::cout << "look speed y: " << this->cameraLookSpeed.y << "\n";

}

void App::mousePositionCallBack(double xpos, double ypos)
{
    if (!this->firstMouse) {
        this->lastMousePosition.x = static_cast<float>(xpos);
        this->lastMousePosition.y = static_cast<float>(ypos);
        this->firstMouse = true;
    }

    glm::vec2 moveAmount{
        xpos - this->lastMousePosition.x,
        this->lastMousePosition.y - ypos,
    };

    this->lastMousePosition.x = static_cast<float>(xpos);
    this->lastMousePosition.y = static_cast<float>(ypos);

    // to disable camera - comment this out
    this->camera.RotateBy(moveAmount.x * this->cameraLookSpeed.x, moveAmount.y * this->cameraLookSpeed.y);

}

bool App::openWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // previously major = 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); // previously minor = 2
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(this->width, this->height, this->appTitle.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    
    // create pointer to window for use inside lambda callback
    glfwSetWindowUserPointer(window, (void*)this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);

        // get the pointer to window so we can assign width and height
        auto a = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
    //    a->width = w;
    //    a->height = h;


        // when adding camera (access using reinterpreted cast pointer)
        a->camera.SetSize(w, h);

    });

    // glad: load all OpenGL function pointers
   // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
        // return -1;
    }


    glEnable(GL_DEPTH_TEST);

    // cull faces in counter-clockwise order
    glFrontFace(GL_CCW);

    // don't draw the back faces
    glCullFace(GL_BACK);

    // enable the feature to cull faces
    glEnable(GL_CULL_FACE);

    return true;
}

//void App::framebuffer_size_callback(GLFWwindow* window, int w, int h)
//{
//    glViewport(0, 0, w, h);
//    //width = w;
//    //height = h;
//}



void App::processInput(GLFWwindow* window)
{
    //if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //    glfwSetWindowShouldClose(window, true);
}