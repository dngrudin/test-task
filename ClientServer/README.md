# ClientServer

Сделать два консольных  приложения.

Первое пишет в TCP/UDP/... сокет сообщение-пакет, содержащее, как минимум, номер пакета, время отправки с точностью до миллисекунд, собственно данные и контрольную сумму данных MD5.  Данные - это массив int16 слов. Размер массива варьируется от 600 до 1600 слов.  Приложение отправляет 1000 пакетов с интервалом 10 мс. Потом спит 10 секунд и отправляет следующие 1000 пакетов с интервалом 10 мс, после чего завершает свою работу. По факту отправки каждого пакета печатает в консоль “Sent: #номер пакета и #время отправки”.

Второе приложение – имеет 2 потока.  Первый поток - слушает сокет и пишет принятые пакеты в кольцевой буфер размером 16 элементов. По факту приёма печатает в консоль “Received: #номер пакета #время приёма и результат проверки контрольной суммы PASS/FAIL”.  Второй поток делает выборку из кольцевого буфера при наличии там необработанных данных и имеет задержку обработки пакета 15 мс. По факту обработки пакета печатает в консоль “Processed: #номер пакета #время окончания обработки и результат проверки контрольной суммы PASS/FAIL”.

Приложения должны работать как на одном компьютере, так и на разных. Компьютеры могут иметь разные архитектуры, например, первый x86, второй PowerPC.

Можно использовать любые Linux библиотеки, но желательно ограничиться использованием стандартных, BOOST и POSIX/Phtreads.
