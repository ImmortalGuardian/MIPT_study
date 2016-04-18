/* ---------------------------------------------------------------------------
 * @
 *					������������ �������������
 *				���������	��������	����������
 *				==================================
 *
 * Build 0x001 04.05.2002
-------------------------------------------------------------------------- */
// �����������
#define N_MAX	10000000

#define VAL_MAX	1000		// ����. ��������� �������� ����������� ���������
#define _NORDTSC			// ��� ��������� ������� ��������� ����������

#include <DoCPU.h>


/* ---------------------------------------------------------------------------
 *
 *				�������� ���������� n ��������� ������� p
 *
--------------------------------------------------------------------------- */
int* linear_sort(int *p, int n)
{
	int a, b;
	int count = 0;
	int *virtual_a;					// ������ ��� ����������

	// �������� ������
	virtual_a = malloc(VAL_MAX*sizeof(int));
	if (!virtual_a) /* ������������ ������ */ return 0;

	// init
	memset(virtual_a, 0, VAL_MAX*sizeof(int));

	// ����������
	for(a = 0; a < n; a++)
		virtual_a[p[a]]++;

	// ������������ ������
	for(a = 0; a < VAL_MAX; a++)
		for(b = 0; b < virtual_a[a]; b++)
			p[count++]=a;

	// ����������� ������
	free(virtual_a);

	return p;
}


/*----------------------------------------------------------------------------
 *
 *							������� ��������� ��� QSORT
 *
--------------------------------------------------------------------------- */
int compare( const void *arg1, const void *arg2 )
{
	return *(int *)arg2 - *(int *)arg1;
}


/*----------------------------------------------------------------------------
 * 
 *				���������� N ����� ���������� ��������� � ���������
 *
--------------------------------------------------------------------------- */
vs(int *p_array, int *p_src, int N)
{
	int a;
	char buf[MAX_STR_LEN];
	#define FORCE ((N>500000)?1:0)

	VVV
	// qsort
	AL_BEGIN
		memcpy(p_array,p_src,N*sizeof(int));
		UL_BEGIN(0, FORCE)
			qsort( (void *)p_array, N, sizeof(int), compare);
		UL_END(0, FORCE)
		VVV;
	AL_END

	// linear sort
	AL_BEGIN
		memcpy(p_array,p_src, N*sizeof(int));
		UL_BEGIN(1, FORCE)
			linear_sort(p_array, N);
		UL_END(1, FORCE)
		VVV
	AL_END
	sprintf(buf,"N %8d %4.5f %4.5f",N,cpu2timeu(Ax_GET(0),FORCE), cpu2timeu(Ax_GET(1),FORCE));
	PRINT(buf);	Lx_OUT("",Ax_GET(0),Ax_GET(1));
}

main()
{
	int a;
	int *p_src, *p_array;

	// TITLE
	PRINT("= = = ������������ ������������� linear_sort ��� qsort = = =\n");
	PRINT_TITLE;

	// �������� ������
	p_src	= malloc(N_MAX*sizeof(int));
	p_array	= malloc(N_MAX*sizeof(int));

	// �������������� ������ ����������� �����
	for (a = 0; a < N_MAX; a++)
		p_src[a]=rand() % VAL_MAX;

	#define VS(N) if(N>N_MAX) {PRINT("-ERR:too big\n");return -1;} else vs(p_array, p_src, N);

	printf(_TEXT("����� ���� tmime qsort/linear(���.) �������������\n"));

	// ���������� 100 �����
	VS(100)

	// ���������� 1.000 �����
	VS(1000)

	// ���������� 10.000 �����
	VS(10000)

	// ���������� 100.000 �����
	VS(100000)

	// ���������� 1.000.000 �����
	VS(1000000)

	// ���������� 10.000.000 �����
	VS(10000000)

	return 0;
}



_P_S()
{
/*
	"�  �������  �� ���������, ������� �������. ����� ��������, ���������. ���
	�����   ���������������   ��,  ������ �  ���������� �  ������  �� �������?
	��  �������,  ���   �����.  �� � ������  ����������� �����, ��������� ����
	�����,  ���� ���  ���  ��� �� ��������, �� ������. �  ���, ��� �����������
	��   ������   �������������  ��������  �����  ���,  ��������   ��   ������
	�����������, � ������ ��������"
									������ �� ����-��������. ��������
*/
}
