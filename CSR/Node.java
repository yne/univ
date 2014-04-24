import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.Random;

public class Node implements Node_I{
	static int FT_SIZE=4;
	static boolean VERBOSE=false;
	
	private int key;
	private HashMap<String,String> table=new HashMap<String,String>();
	
	private Node_I pred=null;
	private Node_I succ=this;
	private Registry reg;
	private Node_I ft[];
	
	public int key() throws RemoteException {return key;}
	public Node_I pred() throws RemoteException {return pred;}
	public void pred(Node_I n) throws RemoteException {pred=n;}
	public Node_I succ() throws RemoteException {return succ;}
	public void succ(Node_I n) throws RemoteException {succ=n;}
	
	Node(Registry reg){
		this(reg,(new Random()).nextInt(Key.SIZE));
	}
	Node(Registry r,int id){
		reg = r;
		key = Key.hash(id);
		this.ft = new Node_I[FT_SIZE];
	}
	public Node_I findSucc(int k)throws RemoteException {
		//System.out.println("jump from "+key+" to "+k);
		if (this == succ || Key.isBetween(k,key, succ.key()) || k==succ.key() || k==key)
			return succ;
		return succ.findSucc(k);
	}
	public void stabilize()throws RemoteException {
		//update Successor
		if (succ.pred() != null && (Key.isBetween(succ.pred().key(),key, succ.key()) || this == succ))
				succ = succ.pred();
		//update Predecessor
		if (succ.pred() == null ||  Key.isBetween(key,succ.pred().key(), succ.key()))
				succ.pred(this);
	}
	public void buildFT(int start_key) throws RemoteException{
		for(int i=0;i<ft.length;i++)
			ft[i]=findSucc(Key.hash(key+(1<<i)));
		//broadcast to the next node
		if(succ.key()!=start_key)
			succ.buildFT(start_key);
	}
	public void save(String key,String value,int k) throws RemoteException{
		table.put(key, value);
		if(k-1>0)succ.save(key, value,k-1);
	}
	public String load(String key,int limit) throws RemoteException{
		if(table.get(key)==null && this.key!=succ.key() && limit>0)
			return succ.load(key,limit-1);
		return table.get(key);
	}
	public String print() throws RemoteException{
		String out="";
		for(int i=0;i<ft.length;i++)out+=ft[i].key()+"\t";
		return "Node : "+key
				+"\tdata : "+table.size()
				+"\tpred : "+(pred!=null?pred.key():"")
				+"\tsucc : "+(succ!=null?succ.key():"")
				+"\tFingers:"+out;
	}
	public String forwardFT(int k,String msg) throws RemoteException{
		if(Key.isBetween(k,pred.key(),key)||k==this.key)
			return "ForwardFT ("+msg+") recu par le Node:"+key;
		if(key<k && k<ft[0].key())
			return ft[0].forwardFT(k,msg);
		for(int i=0;i<ft.length-1;i++)
			if(ft[i+1].key()>k && k>ft[i].key())
				return ft[i].forwardFT(k,msg);
//		if(k>ft[ft.length-1].key())
			return ft[ft.length-1].forwardFT(k,msg);
	}
	public String forward(int k,String msg) throws RemoteException{
		if(Key.isBetween(k,pred.key(),key)||k==this.key)
			return "Forward ("+msg+") received by Node:"+key;
		Node_I target=findSucc(this.key);
		if(VERBOSE)System.out.println(key + "forward to " + target.key());
		return target.forward(k ,msg);
	}
	public void join() throws Exception{
		Node_I bootstrap;
		try{
			//search for the bootstrap node
			//n=(Node_I)reg.lookup("bootstrap");
			bootstrap=(Node_I)LocateRegistry.getRegistry().lookup("Node");
			//no exception = bootstrap exist = tell him I'm the newbie
			//reg.rebind("Node/"+key,(Node_I) UnicastRemoteObject.exportObject(this,0));
			reg=LocateRegistry.createRegistry(key+1100);
			reg.rebind("Node",(Node_I) UnicastRemoteObject.exportObject(this,0));
			//update my context
			succ = bootstrap.findSucc(key);
		}catch(Exception e){
			//no bootstrap found, I'll sacrify myself to the cause
			//reg.rebind("bootstrap", (Node_I) UnicastRemoteObject.exportObject(this,0));
			reg=LocateRegistry.createRegistry(1099);
			reg.rebind("Node",(Node_I) UnicastRemoteObject.exportObject(this,0));
			return;//bootstrap= first = no succ ...
		}
		//post-join work
        Node_I succ_pred = this.succ().pred();
        this.stabilize();
        (succ_pred!=null?succ_pred:this.succ()).stabilize();
		buildFT(key);
		//TODO:retreive_table
    }
	public void quit() throws RemoteException  {
		System.out.println(key+" quit");
		succ.pred(pred);
		pred.succ(succ);
		for(String key : table.keySet())
			succ.save(key, table.get(key), 1);
		succ.buildFT(succ.key());
		
		try {reg.unbind("Node");} catch (NotBoundException e) {}
		UnicastRemoteObject.unexportObject(reg,true);
	}
	
}
