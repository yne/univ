function step(){
	var $op=$('#OP tbody tr:not(.done):last');
	if(!$op.size())return console.log("nothing to process");
	var instr=$op.find('td:first').text().split(/[\s,]/);
	handlers[instr[0]].apply($op,instr.slice(1));
	//must be done later
//	$op.addClass('done');
}
var TableCreate=function(){
	var args=($(this).data('table'));
	window[args.id]=new Array(args.size);
	var html='<thead><tr>'+args.cols.map(function(a){return '<th>'+a+'</th>';}).join('')+'</tr></thead>';
	for(var i=args.size-1;i>=0;i--)
		html+="<tr>"+args.cols.map(function(a){
			return '<td name="'+a+'">'+({b:"0","N":i+args.start}[a]||"")+'</td>';
		}).join('')+"</tr>";
	$(this).html('<table id="'+args.id+'" class="table table-bordered">'+html+'</table>');
}
var TableUpdateAll=function(){
	$('[data-table]').each(function(){
		var t=window[$(this).data('table').id];
		for(var i=0;i<t.length;i++){
			console.log(t[i]);
		}
	});
};
var TablePush=function(){
	
}

var handlers={
	LD:function(src,dst){
		console.log(arguments);
		var N=TamponLoad.push(src,2);
		FloatRegister.push(N,dst);
		this.addClass('success');
	},
	MULTD:function(){
		console.log(arguments);
		this.addClass('done');
	},
	SUBD:function(){
		console.log(arguments);
		this.addClass('done');
	},
	DIVD:function(){
		console.log(arguments);
		this.addClass('done');
	},
	ADDD:function(){
		console.log(arguments);
		this.addClass('done');
	}
}
