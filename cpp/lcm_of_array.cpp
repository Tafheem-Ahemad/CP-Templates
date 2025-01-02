
// Time Complexity is (n log n)

ll lcm_of_array(vector<ll> arr)
{
    ll lcm = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        ll num1 = lcm;
        ll num2 = arr[i];
        ll gcd_val = __gcd(num1, num2);
        lcm = (lcm * num2) / gcd_val;
    }
    return lcm;
}

int main()
{
    while(1){
        if(printf("%d",printf("%d")))
            break;
        else
            continue;
    }
    return 0;
}