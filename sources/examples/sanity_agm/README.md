# sanity_agm

This example aims at verifying that the AGM library is properly working by replaying a test vector and verifying that the algo generates an identical output.
Two test vectors are provided but due to memory limitation, only one can be activated (testing the second one will require a rebuild).

## Specificities of sanity_agm

### Terminal output

Data are printed on the terminal as follow:
```
[I] ###
[I] ### Example Sanity AGM
[I] ###
[I] Running 'out_invn_agm_1' test
[I]    > SUCCESS
```

In case of error, the firmware will print details about which output didn't match as well as the corresponding line in the test vector:
```
[I] ###
[I] ### Example Sanity AGM
[I] ###
[I] Running 'out_invn_agm_1' test
[E]    > /!\ Error on `rv_quat_q30[1]` at line 1069: got 7671502 instead of 7671503
[I]    > FAILURE
```
