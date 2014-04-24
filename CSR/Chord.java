import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Chord {
	public static void print(Node_I n)throws Exception{
		int start_key=n.key();
		do{
	    	System.out.println(n.print());
	    	n=n.succ();
		}while(n.key()!=start_key);
	}
    private static void finish(Node_I n)throws Exception{
		int start_key=n.key();
		do{
	    	n.quit();
		}while(n.key()!=start_key);
	}
	public static void cleanRMI(Registry reg)throws Exception{
		String[] list=reg.list();
		for(int i=0;i<list.length;i++)
			reg.unbind(list[i]);
	}
	
    public static void main(String[] args) {
    	try{
        	//genStatNbNoeud(10, 10, 10, "Amount of Nodes");
        	//genStatDepth(2, 1, 8, "FingerTable Depth");
        	//genStatKey(256, 256, 5, "Max Key Value");
        	TD();
    	}catch(Exception e){
    		System.err.println("RMI Server must be (re)started :\n"+e.getClass());
    		//e.printStackTrace();
    	}
    	System.exit(0);
    }
    public static void saveToNode(Node_I n,String key,String msg) throws RemoteException{
    	n.findSucc(Key.hash(key)).save(key,msg,2);//k=2
    }
    public static String loadFromNode(Node_I n,String key) throws RemoteException{
        return n.findSucc(Key.hash(key)).load(key,5);
    }
    //Exemple du TD
    public static void TD() throws Exception{
        Stat.start("stat_TD.html");
        int keys[]={1,6,8,13,15};
        for(int i=0;i<keys.length;i++)(new Node_Stat(null,keys[i])).join();
        Node_I boot=(Node_I) LocateRegistry.getRegistry().lookup("Node");
        System.out.println(boot.forward(14,"hello"));
        System.out.println(boot.forwardFT(14,"hello"));
        
        saveToNode(boot,"test","hello world from DHT !");
        saveToNode(boot,"smile",":)");
        System.out.println(loadFromNode(boot,"test"));
        Chord.print(boot);
        boot.findSucc(12).quit();
        System.out.println("=== after succ(12) quit ===");
        Chord.print(boot);

        Stat.dump(Key.SIZE);//x axis value
        Stat.end("Key.SIZE");//x axis title
        
        Chord.finish(boot);
    }
	//Generate stats with maximum key value as variable parameter
    public static void genStatKey(int begin, int pas, int cas, String label) throws Exception{
		Stat.start("stat_keyVal_"+begin+"_"+pas+"_"+cas+".html");
		Registry reg=LocateRegistry.getRegistry();
		System.out.println("=== KeySize Stat Gen begin ===");
		for(Key.SIZE = begin; cas-- > 0;  Key.SIZE+=pas){
			System.out.println("Calcul pour une taille de clef de " + Key.SIZE + " en cours...");
            for(int i=0;i<10;i++)(new Node_Stat(reg)).join();
            Node_I boot=(Node_I) reg.lookup("bootstrap");
            boot.forward(Key.SIZE/2,"hello");
            boot.forwardFT(Key.SIZE/2,"hello");		
            cleanRMI(reg);
            Stat.dump(Key.SIZE);
		}
        Stat.end(label);
        System.out.println("=== KeySize Stat Gen end ===");
    }
    
    //Génère des stats avec comme paramètre variable la profondeur des tables
    public static void genStatDepth(int begin, int pas, int cas, String label) throws Exception{
    	Stat.start("stat_depth_"+begin+"_"+pas+"_"+cas+".html");
    	Registry reg=LocateRegistry.getRegistry();
    	Key.SIZE=1024;
    	System.out.println("=== FTDepth Stat Gen begin ===");
    	for(Node.FT_SIZE = begin; cas-- > 0;  Node.FT_SIZE+=pas){
    		System.out.println("Calcul pour une profondeur de " + Node.FT_SIZE + " en cours...");
    		for(int i=0;i<60;i++)(new Node_Stat(reg)).join();
	        Node_I boot=(Node_I) reg.lookup("bootstrap");
	        boot.forward(512,"hello");
	        boot.forwardFT(512,"hello");		
	        cleanRMI(reg);
	        Stat.dump(Node.FT_SIZE);
    	}
        Stat.end(label);
        System.out.println("=== FTDepth Stat Gen end ===");
    }
    
    //Génère des stats avec comme paramètre variable le nombre de noeud dans l'anneau
    public static void genStatNbNoeud(int begin, int pas, int cas, String label) throws Exception{
    	Registry reg=LocateRegistry.getRegistry();
    	Key.SIZE=1024;
    	Stat.start("stat_depth_"+begin+"_"+pas+"_"+cas+".html");
    	System.out.println("=== NbNode Stat Gen begin ===");
    	for(;cas-- > 0; begin+=pas){
    		System.out.println("Calcul pour " + begin + " Nodes en cours...");
    		for(int i=0;i<begin;i++)(new Node_Stat(reg)).join();
	        Node_I boot=(Node_I) reg.lookup("bootstrap");
	        boot.forward(512,"hello");
	        boot.forwardFT(512,"hello");
	        cleanRMI(reg);
	        Stat.dump(begin);
    	}
    	Stat.end(label);
    	System.out.println("=== NbNode Stat Gen end ===");
    }
}
