        sieve[1] = 1;
        for(auto i=2;i<=n;i++){
            if(sieve[i]) continue;
            for(auto j=i;j*i<=right;j++){
                sieve[i*j] = 1;
            }
        } // here sieve[i] = 1 => not prime