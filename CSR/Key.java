
public class Key{
	static int SIZE=64;

	public static int hash(int value){
		return value%SIZE;
	}
	public static int hash(String value){
		return value.hashCode()%SIZE;
	}
	public static boolean isBetween(int me,int a, int b) {
		if(a<b)return (b>me && me>a);
		if(a>b)return (b>me || me>a);
		return false;//from=to
	}
}
