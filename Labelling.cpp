#include <iostream>
#include <vector>

int& get(std::vector<int>& v, int n, int x, int y)
{
    return v[x * n + y];
}

bool inBounds(int x, int y, int m, int n)
{
    return x >= 0 && x < m && y >= 0 && y < n;
}

bool notPrev(int x, int y, int prevX, int prevY)
{
    return x != prevX && y != prevY;
}

bool markObject(std::vector<int> v, std::vector<int>& labelled, std::vector<int>& checked, int m, int n, int x, int y, int prevX, int prevY, int label)
{
    if (get(checked, n, x, y))
    {
        return false;
    }
    get(checked, n, x, y) = 1;

    if (get(v, n, x, y))
    {
        get(labelled, n, x, y) = label;
    }
    else
    {
        return false;
    }

    if (inBounds(x - 1, y, m, n) && notPrev(x - 1, y, prevX, prevY))
    {
        markObject(v, labelled, checked, m, n, x - 1, y, x, y, label);
    }
    if (inBounds(x + 1, y, m, n) && notPrev(x + 1, y, prevX, prevY))
    {
        markObject(v, labelled, checked, m, n, x + 1, y, x, y, label);
    }
    if (inBounds(x, y - 1, m, n) && notPrev(x, y - 1, prevX, prevY))
    {
        markObject(v, labelled, checked, m, n, x, y - 1, x, y, label);
    }
    if (inBounds(x, y + 1, m, n) && notPrev(x, y + 1, prevX, prevY))
    {
        markObject(v, labelled, checked, m, n, x, y + 1, x, y, label);
    }

    return true;
}

std::pair<std::vector<int>, int> getLabelledImage(const std::vector<int>& v, int m, int n)
{
    std::vector<int> labelled(v.size());
    std::vector<int> checked(v.size());
    int label = 1;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!get(labelled, n, i, j))
            {
                label += static_cast<int>(markObject(v, labelled, checked, m, n, i, j, -1, -1, label));
            }
        }
    }

    return std::make_pair(labelled, label);
}

void visualize(std::vector<int>& v, int m, int n)
{
    std::cout << "\n\n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << get(v, n, i, j) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main()
{
    int m = 1;
    int n = 15;
    std::vector<int> v = { 0, 1, 1, 0, 1, 0, 1,1,1,1,1,0,1,1,1};
    visualize(v, m, n);
    auto res = getLabelledImage(v, m, n);
    visualize(res.first, m, n);
}
