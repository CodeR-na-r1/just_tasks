// c++20

#include <iostream>

#include <map>
#include <list>

struct userData
{
	int reqCounter{ 0 };
	std::list<std::pair<int, int>> reqStatistics;
};

int list_analyzer(std::list<std::pair<int, int>>& l, const int& limit, const int& new_time)
{
	int res(0);

	for (auto it = l.begin(); it != l.end(); ++it)
	{
		if (new_time - it->first > limit)
		{
			res += it->second;
		}
		else
		{
			break;
		}
	}

	return res;
}

int list_format(std::list<std::pair<int,int>>& l, const int& limit)
{
	int res(0);

	while (true)
	{
		if (l.back().first - l.front().first > limit)
		{
			res += l.front().second;
			l.pop_front();
		}
		else
		{
			break;
		}
	}

	return res;
}

int main()
{
	std::map<int, userData> usersState;
	std::list<std::pair<int, int>> serviceState;
	serviceState.push_back(std::pair(0, 0));

	int userLimit, serviceLimit, duration;
	std::cin >> userLimit >> serviceLimit >> duration;

	int time, userId;

	int serviceReqCcounter(0);
	while (std::cin >> time >> userId)
	{
		// ------- Проверка условий -------

		if (usersState.contains(userId))
		{
			if (usersState[userId].reqCounter - list_analyzer(usersState[userId].reqStatistics, duration, time) == userLimit)	// Проверка на превышение пользователем лимита запросов с учётом наступившего тайминга (list_analyzer)
			{
				std::cout << "429\n";
				continue;
			}
		}

		if (serviceReqCcounter - list_analyzer(serviceState, duration, time) == serviceLimit)	// Проверка на превышение лимитов запросов к сервису с учётом наступившего тайминга (list_analyzer)
		{
			std::cout << "503\n";
			continue;
		}

		// ------- Обработка данных о запросах пользователя -------

		if (usersState.contains(userId))	// Если пользователь уже есть в списке
		{
			if (usersState[userId].reqStatistics.back().first != time)	// Если новый тайминг
			{
				usersState[userId].reqStatistics.push_back(std::pair(time, 1));	// Добавляем тайминг
				usersState[userId].reqCounter -= list_format(usersState[userId].reqStatistics, duration);	// Обновляем счетчик обращений (стирая неактуальные данные устаревших обращений)
			}
			else
			{
				++usersState[userId].reqStatistics.back().second;	// иначе плюсуем существущий
			}
		}
		else	// иначе добавляем пользователя + инициализируем его тайминг
		{
			usersState[userId] = userData{};
			usersState[userId].reqStatistics.push_back(std::pair<int, int>(time, 1));
		}
		++usersState[userId].reqCounter;	// Префиксный инкремент актуальных таймингов запросов пользователя

		// ------- Обработка данных о всех запросах в сервис -------

		if (serviceState.back().first != time)	// Если новый тайминг
		{
			serviceState.push_back(std::pair(time, 1));
			serviceReqCcounter -= list_format(serviceState, duration);
		}
		else
		{
			++serviceState.back().second;	// иначе плюсуем существущий
		}
		++serviceReqCcounter;	// Префиксный инкремент актуальных таймингов запросов на сервис
		
		std::cout << "200\n";
	}

	return 0;
}