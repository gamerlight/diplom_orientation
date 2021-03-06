# Дипломный проект "Разработка параллельного алгоритма решения уравнения Пуассона для задачи ориентации подводных аппаратов"
## _Используются C++, Qt, OpenMP_

## Блок-схема, реализуемого алгоритма
![Блок-схема алгоритма](https://i.ibb.co/HhPmnpJ/2022-02-21-191514.png)
## Подзадачи данного алгоритма
- Получение данных с внешнего акселерометра и гироскопа (в данном проекте используется плата Arduino с MPU-6050), либо получение данных из файла
- Расчет матрицы перехода C с помощью 9 дифференциальных уравнений вида
![Матричные уравнения](https://i.ibb.co/2jzXk2Q/2022-02-21-191514.png)
- Расчет углов крена, дифферента, рыскания на основе матрицы C (может быть включено в предыдущую подзадачу)
- Расчет координат объекта (с учетом перерасчетов)
- Перерасчет угловой скорости вращения Земли на основе смещения объекта

## Описание реализуемых (уже выполненных и запланированных) классов
- Получение данных (реализовано для устройств, планируется для файлов)
- - SerialPortManager - класс, отвечающий за создание подключения к Arduino
- - QSerialIO - класс, отвечающий за получение данных с устройства
- - StringToFloatMeasurements - класс, отвечающий за перевод единой строки в массив float
- Расчет матрицы C
- Расчет координат
- Перерасчет угловой скорости вращения Земли
- Дополнительные классы
- - inputsettings - диалоговое окно для задания параметров ввода
- - MonitorInput - диалоговое окно для показа считанных строк
