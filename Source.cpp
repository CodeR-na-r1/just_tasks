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
		// ------- �������� ������� -------

		if (usersState.contains(userId))
		{
			if (usersState[userId].reqCounter - list_analyzer(usersState[userId].reqStatistics, duration, time) == userLimit)	// �������� �� ���������� ������������� ������ �������� � ������ ������������ �������� (list_analyzer)
			{
				std::cout << "429\n";
				continue;
			}
		}

		if (serviceReqCcounter - list_analyzer(serviceState, duration, time) == serviceLimit)	// �������� �� ���������� ������� �������� � ������� � ������ ������������ �������� (list_analyzer)
		{
			std::cout << "503\n";
			continue;
		}

		// ------- ��������� ������ � �������� ������������ -------

		if (usersState.contains(userId))	// ���� ������������ ��� ���� � ������
		{
			if (usersState[userId].reqStatistics.back().first != time)	// ���� ����� �������
			{
				usersState[userId].reqStatistics.push_back(std::pair(time, 1));	// ��������� �������
				usersState[userId].reqCounter -= list_format(usersState[userId].reqStatistics, duration);	// ��������� ������� ��������� (������ ������������ ������ ���������� ���������)
			}
			else
			{
				++usersState[userId].reqStatistics.back().second;	// ����� ������� �����������
			}
		}
		else	// ����� ��������� ������������ + �������������� ��� �������
		{
			usersState[userId] = userData{};
			usersState[userId].reqStatistics.push_back(std::pair<int, int>(time, 1));
		}
		++usersState[userId].reqCounter;	// ���������� ��������� ���������� ��������� �������� ������������

		// ------- ��������� ������ � ���� �������� � ������ -------

		if (serviceState.back().first != time)	// ���� ����� �������
		{
			serviceState.push_back(std::pair(time, 1));
			serviceReqCcounter -= list_format(serviceState, duration);
		}
		else
		{
			++serviceState.back().second;	// ����� ������� �����������
		}
		++serviceReqCcounter;	// ���������� ��������� ���������� ��������� �������� �� ������
		
		std::cout << "200\n";
	}

	return 0;
}