/* readline함수를 사용하기위한 헤더 */
# include <readline/readline.h>
/* add_history함수를 사용하기위한 헤더 */
# include <readline/history.h>
/* readline함수를 활용하여 간단한 프로그램 작성하기 */
int main(void)
/* readline함수의 리턴값을 저장하기위해 임의로 포인터를 하나 선언한다 */
    char *str;
/* 무한루프를 돌리면서 readline();함수를 반복적으로 호출할 것이다 */
        /* readline함수가 호출되면 인자(prompt : )를 터미널에 출력하고 저장할 라인을 입력받는다 */
        str = readline("prompt : ");/* read함수는 저장한 문자열의 메모리주소를 반환한다 */
            break ;/* 반복문을 탈출해준다.*/
	/* add_history에 저장된 문자열은 up & down 방향키를 이용해 확인할수있다 */
        add_history(str);
