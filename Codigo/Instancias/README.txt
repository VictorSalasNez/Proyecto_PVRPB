SET P1

VRP instances
Nr. of Depots: 1
Nr. of Stops: 10

Linehaul - Backhau
Nr. of Vehicles: 11
Capacity of Vehicles:Q=700

File structure

NODE_COORD_SECTION
1	0	0
2	-5	70
|  |  |
|  |  Y coordinate
|  X coordinate
Cliente

NODE_DEMANDA_TIPO_7DIAS

1               0             0            0             0              0             0             0  (depot)
2          855    1   319   1     49   1   847   0   484    0   227   1   668   0 (stop 1)
	....                                     ...
101        17   1    566   0   257   0  1015  1   603   0   	659   0   347   1 (stop 100)
|           |   |      |   |    |    |    |   |     |   |        |   |     |   |
|           |   |      |   |    |    |    |   |     |   |        |   |     |   delivery=0 / pickup=1 Day 7
|           |   |      |   |    |    |    |   |     |   |        |   |      demand day 7
|           |   |      |   |    |    |    |   |     |   |        |   delivery=0 / pickup=1 Day 6
|           |   |      |   |    |    |    |   |     |   |        demand day 6
|           |   |      |   |    |    |    |   |     |   delivery=0 / pickup=1 Day 5
|           |   |      |   |    |    |    |   |     demand day 5
|           |   |      |   |    |    |    |   delivery=0 / pickup=1 Day 4
|           |   |      |   |    |    |    demand day 4
|           |   |      |   |    |   delivery=0 / pickup=1 Day 3
|           |   |      |   |    demand day 3
|           |   |      |   delivery=0 / pickup=1 Day 2
|           |   |      demand day  2
|           |   delivery=0 / pickup=1 Day 1
|           demand day  1
Cliente
stop nr.
