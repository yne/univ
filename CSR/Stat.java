import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.Vector;

public class Stat {
	private static HashMap<String,Vector<Integer>> data;
	private static BufferedWriter out;
	private static int iter=0;
	private static String fcn="i";//first col name (x axis values)
	
	public static void start(String fname) throws IOException{
		iter=0;
		data=new HashMap<String, Vector<Integer>>();
		set(fcn,0,0);
		out= new BufferedWriter(new FileWriter(fname,false));
		out.write("<!DOCTYPE html><html style='height:100%;overflow:hidden;'><head><script src='https://www.google.com/jsapi'></script><script>\n"+
		"google.load('visualization', '1', {packages:['corechart']});google.setOnLoadCallback(function(){"+
		"(new google.visualization.LineChart(chart)).draw(google.visualization.arrayToDataTable([\n");
	}
	public static void dump() throws IOException{dump(iter);}
	public static void dump(Integer i) throws IOException{
		set("i",iter,i);
		iter++;
	}
	public static void end(String label) throws IOException{
		//print collumn name row
		out.write("['"+fcn+"',");
		for(Entry<String, Vector<Integer>> entry:data.entrySet())
			if(entry.getKey()!=fcn)out.write("'"+entry.getKey()+"',");
		out.write("],\n");
		//print values rows
		for(int i=0;i<iter;i++){
			out.write("["+get(fcn,i)+",");
			for(String key:data.keySet())
				if(key!=fcn)out.write(get(key,i)+",");
			out.write("],\n");
		}
		out.write("]), {hAxis:{title: '"+label+"'},vAxis:{logScale:true},title: 'RMI Profiler'});});"+
		"</script></head><body id='chart' style='height: 100%;margin: 0px;'></body></html>");
		out.close();
		data.clear();
	}
	public static Integer get(String key,int pos){
		if(!data.containsKey(key))data.put(key, new Vector<Integer>());
		Vector<Integer> v=data.get(key);
		while(v.size()<=iter)v.add(0);
		return v.get(pos);
	}
	public static void set(String key,int pos,Integer value){
		if(!data.containsKey(key))data.put(key, new Vector<Integer>());
		Vector<Integer> v=data.get(key);
		while(v.size()<=iter)v.add(0);
		v.set(iter, value);
		data.put(key, v);
	}
	
	public static void log(String key) {
		set(key,iter,get(key,iter)+1);
	}
}
