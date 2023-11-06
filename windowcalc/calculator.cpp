#include <Windows.h>
#include <string>
#include "resource.h"

// название класса окна
#define WINCLASS_NAME "WinCalc"

const int WIDTH = 400;	// ширина окна
const int HEIGHT = 600;	// высота окна

const int buttonSize = 60;	// размер кнопки
const int buttonDist = 10;	// расстояние между кнопками
const int buttonBegX = 55;	// начало кнопок x
const int buttonBegY = 160;	// Начало кнопок y
RECT AnsRect{ 20, 10, WIDTH - 25, buttonBegY - 10 }; // прямоугольник вывода чисел ответа
RECT TempRect{ 20, 10, WIDTH /2 - 25, buttonBegY /2 - 10 }; // прямоугольник вывода временных чисел

#define plus 10
#define minus 11
#define multi 12
#define divis 13
#define equals 14
#define del 15
#define dot 16
#define clear_all 17

std::string ans = "0";	// число, отображаемое в калькуляторе
std::string temp = "";	// временная переменная
auto FontAns = CreateFont(50, 20, 3, 0, 3, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);	// шрифт для ответа
auto FontTemp = CreateFont(20, 10, 3, 0, 3, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);	// шрифт для временного значения
bool GotAns = false; // был ли получен ответ 

void DrawNumbers(HDC hdc)	// прорисовка чисел в квадрате
{
	SelectObject(hdc, FontAns);
	SetBkColor(hdc, RGB(240, 240, 240));
	SelectObject(hdc, (HPEN)GetStockObject(BLACK_PEN));
	SelectObject(hdc, CreateSolidBrush(RGB(240, 240, 240)));
	Rectangle(hdc, 10, 10, WIDTH - 25, buttonBegY - 10);
	// максимальное число разрядов - 14, дальше не показывать
	std::string tempStr; // временная переменная для хранения огромных чисел
	if (ans.size() > 14)	// урезаем количество цифр
	{
		tempStr = { ans.begin(), ans.begin() + 11 };
		tempStr += "...";
	}
	else	// если меньше 14
	{
		tempStr = ans;
	}
	DrawText(hdc, tempStr.c_str(), (int)tempStr.size(), &AnsRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	SelectObject(hdc, FontTemp);
	if (temp.size() > 14)	// урезаем количество цифр
	{
		tempStr = { temp.begin(), temp.begin() + 11 };
		tempStr += "...";
	}
	else	// если меньше 14
	{
		tempStr = temp;
	}
	DrawText(hdc, tempStr.c_str(), (int)tempStr.size(), &TempRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	if (ans == "Error")	// если произошла ошибка при вычислениях
	{
		ans = "0";
		temp = "";
	}
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
		if (LOWORD(wparam) >= '0' && LOWORD(wparam) <= '9')	// если вводится число
		{
			if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))	// если был нажат shift
				PostMessage(hwnd, WM_COMMAND, multi, 0);
			else
				PostMessage(hwnd, WM_COMMAND, wparam - 48, 0);
		}
		else if (LOWORD(wparam) >= 96 && LOWORD(wparam) <= 105)	// ввод чисел с нампада
		{
			PostMessage(hwnd, WM_COMMAND, wparam - 96, 0);
		}
		else
		{
			switch (wparam)	// если нажата любая другая клавиша
			{
			case 187:	//  клавиша =+
			{
				if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))	// если был нажат shift
					PostMessage(hwnd, WM_COMMAND, plus, 0);
				else
					PostMessage(hwnd, WM_COMMAND, equals, 0);	// shift не был нажат
				break;
			}
			case 107:	// плюс на нампаде
			{
				PostMessage(hwnd, WM_COMMAND, plus, 0);
				break;
			}
			case 189:	// минус
			{
				PostMessage(hwnd, WM_COMMAND, minus, 0);
				break;
			}
			case VK_SUBTRACT:	// минус на нампаде
			{
				PostMessage(hwnd, WM_COMMAND, minus, 0);
				break;
			}
			case 106:	// умножение на нампаде
			{
				PostMessage(hwnd, WM_COMMAND, multi, 0);
				break;
			}
			case 111:	// деление на нампаде
			{
				PostMessage(hwnd, WM_COMMAND, divis, 0);
				break;
			}
			case 191:	// деление
			{
				PostMessage(hwnd, WM_COMMAND, divis, 0);
				break;
			}
			case 190:	// точка
			{
				PostMessage(hwnd, WM_COMMAND, dot, 0);
				break;
			}
			case 188:	// запятая
			{
				PostMessage(hwnd, WM_COMMAND, dot, 0);
				break;
			}
			case VK_RETURN:	// enter
			{
				PostMessage(hwnd, WM_COMMAND, equals, 0);
				break;
			}
			case VK_DELETE:	// delete
			{
				PostMessage(hwnd, WM_COMMAND, del, 0);
				break;
			}
			case VK_BACK:	// backspace
			{
				PostMessage(hwnd, WM_COMMAND, del, 0);
				break;
			}
			case VK_ESCAPE:	// escape
			{
				PostMessage(hwnd, WM_COMMAND, clear_all, 0);
				break;
			}
			default:break;
			}
		}
		return 0;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wparam) >= 0 && LOWORD(wparam) < 10)	// если вводится число
		{
			if (ans == "0")
				ans = "";
			if (GotAns)
			{
				ans = "";
				GotAns = false;	// ввод нового числа после получения ответа
			}
			ans += std::to_string(LOWORD(wparam));
			PostMessage(hwnd, WM_PAINT, 0, 0);
		}
		else if (LOWORD(wparam) == del)	// если удаляется цифра
		{
			// удаление последней цифры числа
		ans.erase(ans.end() - 1);
		if (ans.size() == 0)
			ans = "0";
		}
		else if (LOWORD(wparam) == dot)	// если вводится точка
		{
			if (GotAns)
			{
				GotAns = false;
				ans = "0.";
			}
			else if (ans.find('.') == std::string::npos)
				ans += '.';
		}
		else if (LOWORD(wparam) == clear_all)	// если производится очистка выражения
		{
			ans = "0";
			temp = "";
		}
		else
		{
			switch (LOWORD(wparam))
			{
			case plus:
			{
				// операция сложения
				if (temp == "")
				{
					temp = ans + '+';
					ans = temp;
					ans.erase(ans.end() - 1);
				}
				else if(!(temp.back() >= '0' && temp.back() <= '9'))
				{
					temp.erase(temp.end() - 1);
					temp += '+';
				}
				break;
			}
			case minus:
			{
				// операция вычитания
				if (temp == "")
				{
					temp = ans + '-';
					ans = temp;
					ans.erase(ans.end() - 1);
				}
				else if (!(temp.back() >= '0' && temp.back() <= '9'))
				{
					temp.erase(temp.end() - 1);
					temp += '-';
				}
				break;
			}
			case divis:
			{
				// операция деления
				if (temp == "")
				{
					temp = ans + '/';
					ans = temp;
					ans.erase(ans.end() - 1);
				}
				else if (!(temp.back() >= '0' && temp.back() <= '9'))
				{
					temp.erase(temp.end() - 1);
					temp += '/';
				}
				break;
			}
			case multi:
			{
				// операция умножения
				if (temp == "")
				{
					temp = ans + '*';
					ans = temp;
					ans.erase(ans.end() - 1);
				}
				else if (!(temp.back() >= '0' && temp.back() <= '9'))
				{
					temp.erase(temp.end() - 1);
					temp += '*';
				}
				break;
			}
			case equals:
			{
				// операция равенства
				if (temp.size() == 0) // если строка пустая
				{
					temp = ans;
				}
				else if (!(temp.back() >= '0' && temp.back() <='9'))
				{
					switch (temp.back())	// какое действие выполнять
					{
					case '+':
					{
						ans = std::to_string(stof(temp) + stof(ans));
						break;
					}
					case '-':
					{
						ans = std::to_string(stof(temp) - stof(ans));
						break;
					}
					case '*':
					{
						ans = std::to_string(stof(temp) * stof(ans));
						break;
					}
					case '/':
					{
						if (stof(ans) == 0)	// на ноль нельзя делить
						{
							ans = "Error";
							temp = ans;
						}
						else
						{
							ans = std::to_string(stof(temp) / stof(ans));
						}
						break;
					}
					default:break;
					}
					if (ans != "Error" && stof(ans) == (int)stof(ans))	// если получилось целое число, то не выводить дробную часть
						ans = std::to_string((int)stof(ans));
					if (ans != "Error" && stof(temp) == (int)stof(temp))
						temp = std::to_string((int)stof(temp));	// если получилось целое число, то не выводить дробную часть
				}
				temp = ans + '=';	// добавить к ответу знак равенства
				break;
			}
			default: break;
			}
			GotAns = true;
		}
		hdc = GetDC(hwnd);
		DrawNumbers(hdc);
		ReleaseDC(hwnd, hdc);
		SetFocus(hwnd);
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
	winclass.hIcon = LoadIcon(hinstance,MAKEINTRESOURCE(IDI_ICON1));
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = CreateSolidBrush(RGB(200,200,200));
	winclass.lpszClassName = WINCLASS_NAME;
	winclass.lpszMenuName = NULL;
	winclass.hIconSm = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON1));
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
		WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN,
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
CreateWindowEx(NULL, "button", "C", WS_VISIBLE | WS_CHILD, buttonBegX + 2*(buttonSize + buttonDist), buttonBegY, buttonSize, buttonSize, hwnd, (HMENU)clear_all, hinstance, NULL);
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