all:
	gcc cpuinfo.c -o cpuinfo
	gcc disques.c -o disques
	gcc idle.c -o idle
	gcc kern.c -o kern
	gcc p_env.c -o p_env