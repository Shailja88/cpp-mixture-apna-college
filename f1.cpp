#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    int key = t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        int a[n];
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        // solution
        if (k * 2 < n)
        {
            cout << "Case #" <<  key-t  << ": NO" << endl;
        }
        else
        {
            int a_count[101] = {0};
            for (int i = 0; i < n; i++)
            {
                a_count[a[i]] += 1;
            }
            for (int i = 0; i <= 100; ++i)
            {
                if (a_count[i] >= 3)
                {
                    cout << "Case #" <<  key-t << ": NO" << endl;
                    break;
                }
                else if (i == 100)
                {
                    cout << "Case #" << key-t<< ": YES" << endl;
                }
            }
        }
    }

    return 0;
}