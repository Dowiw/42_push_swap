# 42_push_swap
TODO

To test:
```
ARG="$(shuf -i 0-100 -n 100 | paste -sd' ')"; ./push_swap $ARG | wc -l
ARG="$(shuf -i 0-100 -n 100 | paste -sd' ')"; ./push_swap $ARG | ./checker_linux $ARG
```
