# 14889


def sum_of(team):
    sum = 0
    for i in range(len(team) - 1):
        for j in range(i + 1, len(team)):
            a = team[i]
            b = team[j]
            sum += ability[a][b] + ability[b][a]
    return sum


def re(index, team):
    team.add(index)
    if len(team) == N / 2:
        get_diff_and_check_maximum(team)
    else:
        for i in range(index + 1, N):
            re(i, team.copy())


def get_diff_and_check_maximum(team):
    global MIN

    team1 = list(team)
    team2 = get_diff_set_as_list(TEAM, team)

    diff = abs(sum_of(team1) - sum_of(team2))
    MIN = MIN if MIN < diff else diff


def get_diff_set_as_list(set1, set2):
    return [x for x in set1 if x not in set2]


MIN = 2 ** 31

N = input()

ability = []
TEAM = set()
for i in range(N):
    ability.append(map(int, raw_input().split()))
    TEAM.add(i)

re(0, set())

print MIN
