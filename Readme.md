# Mini (micro) docs for Display module

## Display
## Usage

Сначала нужно поставить себе ncurses чтобы всё точно работало.
На маке - через brew. Разберетесь.
Ubuntu/Debian/Kali etc...

```bash
sudo apt-get install libncursesw5-dev
```

```cpp
Display display; //Можно сделать любое количество объектов типа Display.
Display display2; //Считайте, что это бесплатно. Запросы можно посылать в любой объект дисплея.
Display display3; //На протяжении всего рантайма должен существовать хотя бы один объект дисплея, 
//когда уничтожается последний объект всё стирается и работа завершается. Держите хотя бы один объект созданным (хотя мы скорее всего просто сделаем один дисплей в мейне)
```

НЕ СТОИТ СОЗДАВАТЬ static объекты дисплея. Это приводит к ошибкам. Лучше каждый раз создать новый объект. Помните - это бесплатно.

```cpp
WindowEvent event(WindowEvent::INFO, std::to_string(key)); //В данном случае WindowEvent - это то, что будет 
//отправлено, напечатано в окно с текстом.  
display.SendEvent(event);
```

```cpp
struct WindowEvent{
    enum EventType{
        NONE, //Send without any color and [announcment] IDK when should you use, but you can debug with it)
        INFO, //Important info, Blue color
        ACTION, //Very important actions (e.x. in figth), Red color
        REPLY //For something that someone says, Orange color
    } type;
    std::string WindowEventString;
    std::string Author; //For REPLY only
    explicit WindowEvent(EventType type, std::string WindowEventString, std::string Author = "");
    //Тут код сам по себе описывает всё, что можно отправить в окно с текстом, если чего-то не хватает - смело пишите мне - добавим.
};
```
## Использование спрайтов и создание цветов.

Почти все спрайты предвариательно отрисованы (пока нет но будут). И лежат в виде функций в namespace под названием Drawer.
Однако, если есть желание, то спрайты можно рисовать самостоятельно.

## Usage



```cpp
//Создаем объект с помощью которого можно создавать пары цветов и сами цвета
ColorManager manager;
unsigned colorPair = manager.CreateColorPair(ColorManager::getColor(0, 255, 153), -1); //Создаем салатовые буквы на стандартном фоне
//Каждая пара цветов имеет тип unsigned. Каждый цвет - short и значение 0-255.
//CreateColorPair создаёт пару из двух цветов. Первый параметр - цвет буквы. Второй - цвет фона.
//Значение цвета -1 означает стандартный цвет. Для цвета текста - белый. Для фона чёрный.
//С помощью static метода getColor(int R, int G, int B) можно получить цвет, максимально близкий к заданному цвету в формате rgb.
//Всего доступно 256 цветов, поэтому выбран будет максимально ПОХОЖИЙ.
```

Так же существует 8 стандартных цветов.
```
#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7
```


Создаем спрайт
Спрайт, это двумерный вектор из символов. Каждый символ - это char | ATTRIBUTES | colorPair.
Где | это оператор побитового ИЛИ.
colorPair описан выше.
ATTRIBUTES - это набор из атрибутов из следующего списка, соединенный с помощью побитового ИЛИ:
```
A_ITALIC - italic шрифт
A_BLINK - мерцающий
A_UNDERLINE - подчеркнутый
A_ALTCHARSET - другой набор символов (погуглите)
A_BOLD - жирный
A_DIM - половинная яркость
A_REVERSE - развернутый символ
A_INVIS - невидимый симовол 
```
Существуют и другие возможные аттрибуты. [тык](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/attrib.html)

Теперь действительно создаем спрайт:
```cpp
std::vector<std::vector<unsigned>> sprite = {{176u | colorPair, 0, 'X' | colorPair, 'X' | colorPair, 'X' | colorPair}};
```

Важное замечание.
Тут 176u - это unsigned со значением 176.
0 !БЕЗ АТРИБУТОВ это "прозрачный пиксель". Чтобы спрайты можно было накладывать друг на друга.

```cpp
display.DrawSprite(sprite, 10, 10); //координаты в виде x, y считая от левого верхнего угла
display.ClearGraphixWindow(); //Полностью очистит экран
```
Обратите внимание, что если спрайт не поместится на экран - то будет брошено исключение std::runtime_error.

