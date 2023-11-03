#include <Windows.h>
#include <string>

#define WINCLASS_NAME "WinCalc"
#define plus 1

const int WIDTH = 400;	// ширина окна
const int HEIGHT = 600;	// высота окна

const int buttonSize = 60;	// размер кнопки
const int buttonDist = 10;	// расстояние между кнопками
const int buttonBegX = 55;	// начало кнопок x
const int buttonBegY = 160;	// Начало кнопок y
RECT AnsRect{ 20, 10, WIDTH - 25, buttonBegY - 10 }; // прямоугольник вывода чисел

#define plus 10
#define minus 11
#define multi 12
#define divis 13
#define equals 14
#define del 15
#define dot 16

std::string ans = "0";
float temp = 0;
auto FONT = CreateFont(50, 20, 3, 0, 3, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

void DrawNumbers(HDC hdc)	// прорисовка чисел в квадрате
{
	SelectObject(hdc, FONT);
	SetBkColor(hdc, RGB(240, 240, 240));
	SelectObject(hdc, (HPEN)GetStockObject(BLACK_PEN));
	SelectObject(hdc, CreateSolidBrush(RGB(240, 240, 240)));
	Rectangle(hdc, 10, 10, WIDTH - 25, buttonBegY - 10);
	DrawText(hdc, ans.c_str(), ans.size(), &AnsRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (msg)
	{
	case WM_CREATE:
	{
		return 0;
		break;
	}
	case WM_PAINT:
	{
		// графон
		hdc = BeginPaint(hwnd, &ps);
		DrawNumbers(hdc);
		MoveToEx(hdc, buttonBegX / 2, buttonBegY + 10, NULL);
		LineTo(hdc, buttonBegX / 2, HEIGHT - 50);
		MoveToEx(hdc, WIDTH - 35, buttonBegY + 10, NULL);
		LineTo(hdc, WIDTH - 35, HEIGHT - 50);
		MoveToEx(hdc, WIDTH - 35, HEIGHT - 50, NULL);
		LineTo(hdc, buttonBegX / 2 - 1, HEIGHT - 50);
		EndPaint(hwnd, &ps);
		return 0;
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wparam)
		{
		case '1':
		{
			return 0;
		}
		case '2':
		{
			return 0;
		}
		case '3':
		{
			return 0;
		}
		case '4':
		{
			return 0;
		}
		case '5':
		{
			return 0;
		}
		case '6':
		{
			return 0;
		}
		case '7':
		{
			return 0;
		}
		case '8':
		{
			return 0;
		}
		case '9':
		{
			return 0;
		}
		case '0':
		{
			return 0;
		}
		default:break;
		}
	}
	case WM_COMMAND:
	{
		if (LOWORD(wparam) >= 0 && LOWORD(wparam) < 10)	// если вводится число
		{
			if (ans == "0")
				ans = "";
			ans += std::to_string(LOWORD(wparam));
			PostMessage(hwnd, WM_PAINT, 0, 0);
		}
		else
		{
			switch (LOWORD(wparam))
			{
			case plus:
			{
				break;
			}
			case minus:
			{
				break;
			}
			case divis:
			{
				break;
			}
			case multi:
			{
				break;
			}
			case equals:
			{
				break;
			}
			case del:
			{
				// удаление последней цифры числа
				ans.erase(ans.end()-1);
				if (ans.size() == 0)
					ans = "0";
				break;
			}
			case dot:
			{
				break;
			}
			default: break;
			}
		}
		hdc = GetDC(hwnd);
		DrawNumbers(hdc);
		ReleaseDC(hwnd, hdc);
		return 0;
	}
	default: break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(_In_ HINSTANCE hinstance,_In_opt_ HINSTANCE hprevinstance,_In_ LPSTR lpcmdline,_In_ int ncmdshow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX winclass, winbutton;

//////////////////////////// класс окна
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = NULL;
	winclass.lpfnWndProc = WinProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra =0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = CreateSolidBrush(RGB(200,200,200));
	winclass.lpszClassName = WINCLASS_NAME;
	winclass.lpszMenuName = NULL;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//////////////////////////// класс кнопки
	winbutton.cbSize = sizeof(WNDCLASSEX);
	winbutton.style = NULL;
	winbutton.lpfnWndProc = WinProc;
	winbutton.cbClsExtra = 0;
	winbutton.cbWndExtra = 0;
	winbutton.hInstance = hinstance;
	winbutton.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winbutton.hCursor = LoadCursor(NULL, IDC_ARROW);
	winbutton.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winbutton.lpszClassName = "button";
	winbutton.lpszMenuName = NULL;
	winbutton.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//////////////////////////////////

// регистрирование класс
	if (!RegisterClassEx(&winclass))
		return 0;

// создание главного окна
	if (!(hwnd = CreateWindowEx(
		NULL,
		WINCLASS_NAME,
		"CALCULATOR",
		WS_VISIBLE | WS_SYSMENU,
		200, 200,
		WIDTH, HEIGHT,
		NULL,
		NULL,
		hinstance,
		NULL)))
		return 0;

// расположение кнопок
CreateWindowEx(NULL, "button", "+", WS_VISIBLE | WS_CHILD, buttonBegX, buttonBegY, buttonSize, buttonSize, hwnd, (HMENU)plus, hinstance, NULL);
CreateWindowEx(NULL, "button", "Del", WS_VISIBLE | WS_CHILD, buttonBegX + buttonSize + buttonDist, buttonBegY, buttonSize, buttonSize, hwnd, (HMENU)del, hinstance, NULL);
CreateWindowEx(NULL, "button", "-", WS_VISIBLE | WS_CHILD, buttonBegX, buttonBegY + (buttonSize + buttonDist), buttonSize, buttonSize, hwnd, (HMENU)minus, hinstance, NULL);
CreateWindowEx(NULL, "button", "/", WS_VISIBLE | WS_CHILD, buttonBegX, buttonBegY + 2*(buttonSize + buttonDist), buttonSize, buttonSize, hwnd, (HMENU)divis, hinstance, NULL);
CreateWindowEx(NULL, "button", "*", WS_VISIBLE | WS_CHILD, buttonBegX, buttonBegY + 3*(buttonSize + buttonDist), buttonSize, buttonSize, hwnd, (HMENU)multi, hinstance, NULL);
CreateWindowEx(NULL, "button", "=", WS_VISIBLE | WS_CHILD, buttonBegX, buttonBegY + 4*(buttonSize + buttonDist), buttonSize, buttonSize, hwnd, (HMENU)equals, hinstance, NULL);
CreateWindowEx(NULL, "button", ",", WS_VISIBLE | WS_CHILD, buttonBegX + buttonSize + buttonDist, buttonBegY + 4 * (buttonSize + buttonDist), buttonSize, buttonSize, hwnd, (HMENU)dot, hinstance, NULL);
CreateWindowEx(NULL, "button", "1", WS_VISIBLE | WS_CHILD, buttonBegX + buttonSize + buttonDist, buttonBegY + (buttonDist + buttonSize), buttonSize, buttonSize, hwnd, (HMENU)1, hinstance, NULL);
CreateWindowEx(NULL, "button", "2", WS_VISIBLE | WS_CHILD, buttonBegX + 2 * (buttonSize + buttonDist), buttonBegY + (buttonDist + buttonSize), buttonSize, buttonSize, hwnd, (HMENU)2, hinstance, NULL);
CreateWindowEx(NULL, "button", "3", WS_VISIBLE | WS_CHILD, buttonBegX + 3 * (buttonSize + buttonDist), buttonBegY + (buttonDist + buttonSize), buttonSize, buttonSize, hwnd, (HMENU)3, hinstance, NULL);
CreateWindowEx(NULL, "button", "4", WS_VISIBLE | WS_CHILD, buttonBegX + buttonSize + buttonDist, buttonBegY + 2*(buttonDist + buttonSize), buttonSize, buttonSize, hwnd, (HMENU)4, hinstance, NULL);
CreateWindowEx(NULL, "button", "5", WS_VISIBLE | WS_CHILD, buttonBegX + 2 * (buttonSize + buttonDist), buttonBegY + 2*(buttonDist + buttonSize), buttonSize, buttonSize, hwnd, (HMENU)5, hinstance, NULL);
CreateWindowEx(NULL, "button", "6", WS_VISIBLE | WS_CHILD, buttonBegX + 3 * (buttonSize + buttonDist), buttonBegY + 2*(buttonDist + buttonSize), buttonSize, buttonSize, hwnd, (HMENU)6, hinstance, NULL);
CreateWindowEx(NULL, "button", "7", WS_VISIBLE | WS_CHILD, buttonBegX + buttonSize + buttonDist, buttonBegY + 3 * (buttonDist + buttonSize), buttonSize, buttonSize, hwnd, (HMENU)7, hinstance, NULL);
CreateWindowEx(NULL, "button", "8", WS_VISIBLE | WS_CHILD, buttonBegX + 2 * (buttonSize + buttonDist), buttonBegY + 3 * (buttonDist + buttonSize), buttonSize, buttonSize, hwnd, (HMENU)8, hinstance, NULL);
CreateWindowEx(NULL, "button", "9", WS_VISIBLE | WS_CHILD, buttonBegX + 3 * (buttonSize + buttonDist), buttonBegY + 3 * (buttonDist + buttonSize), buttonSize, buttonSize, hwnd, (HMENU)9, hinstance, NULL);
CreateWindowEx(NULL, "button", "0", WS_VISIBLE | WS_CHILD, buttonBegX + 2 * (buttonSize + buttonDist), buttonBegY + 4 * (buttonDist + buttonSize), buttonSize, buttonSize, hwnd, (HMENU)0, hinstance, NULL);
//

// главный цикл
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
//
	return msg.message;
}