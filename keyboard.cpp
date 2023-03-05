#include <iostream>
#include <SDL.h>
//#include <SDL2/SDL.h>

using namespace std;

//**************************************************************
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Keyboard in SDL";

void logSDLError(std::ostream& os, 
                 const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
//**************************************************************

void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    // Your code here
    SDL_Event e;

    // Định nghĩa toạ độ ban đầu và kích cỡ hình chữ nhật
    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH / 2;
    filled_rect.y = SCREEN_HEIGHT / 2;
    filled_rect.w = 16;
    filled_rect.h = 12;
    // Bước nhảy mỗi khi dịch chuyển
    int step = 4;
    // Xoá toàn bộ màn hình và vẽ
    refreshScreen(window, renderer, filled_rect);

    while (true) {
        // Đợi 10 mili giây
        SDL_Delay(10);

        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
        if ( SDL_WaitEvent(&e) == 0) continue; 
        
        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (e.type == SDL_QUIT) break;

        // Nếu có một phím được nhấn, thì xét phím đó là gì để xử lý tiếp
        if (e.type == SDL_KEYDOWN) {
            // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
            if (e.key.keysym.sym == SDLK_ESCAPE) break;

            // Nếu phím mũi tên trái, dịch sang trái 
            // (cộng chiều rộng, trừ bước, rồi lấy phần dư để giá trị luôn dương, và hiệu ứng quay vòng)
            if (e.key.keysym.sym == SDLK_LEFT) filled_rect.x = (filled_rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
            // Tương tự với dịch phải, xuống và lên
            if (e.key.keysym.sym == SDLK_RIGHT) filled_rect.x = (filled_rect.x + step) % SCREEN_WIDTH;
            if (e.key.keysym.sym == SDLK_DOWN) filled_rect.y = (filled_rect.y + step) % SCREEN_HEIGHT;
            if (e.key.keysym.sym == SDLK_UP) filled_rect.y = (filled_rect.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
            
            // Xoá toàn bộ màn hình và vẽ lại
            refreshScreen(window, renderer, filled_rect);
        }
    }
    
    quitSDL(window, renderer);
    return 0;
}

// Xoá và vẽ lại toàn bộ màn hình với 1 hình chữ nhật
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect)
{
    // Đặt màu vẽ thành xanh lam (blue), xoá màn hình về màu xanh lam.
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);   // blue
    SDL_RenderClear(renderer);
    
    // Đặt màu vẽ về trắng và vẽ hình chữ nhật
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    SDL_RenderFillRect(renderer, &filled_rect);

    // Dùng lệnh hiển thị (đưa) hình đã vẽ ra mành hình
   //Khi thông thường chạy với môi trường bình thường ở nhà
    SDL_RenderPresent(renderer);
   //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   //SDL_UpdateWindowSurface(window);
}


//*****************************************************
// Các hàm chung về khởi tạo và huỷ SDL
void logSDLError(std::ostream& os, 
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) 
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, 
    //   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | 
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
//**************************************************************

