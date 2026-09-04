/**
 * 生成目录树及文件内容
 * @author zhangss
 * @date 2014-04-24
*/
var FileView = {
		
	_types: [{type: 'x-status/info1', view: 'text'}],//文件内容类型{type: 'x-status/info1', view: 'json'}
	
	loadFile: function(fileType, content){
		this.initTypes();
		fileType = $.trim(fileType);
		var obj = this._types[fileType];
		if(obj){
			if(obj.view && obj.view == 'text'){
				ViewOper.textRender(content);
			}
		}else{
			alert('Not found view type');
		}
	},
	
	initTypes: function(){
		for(var i=0; i < this._types.length; i++){
			var obj = this._types[i];
			this._types[obj.type] = obj;
		}
	}
	
}

/**************************************************************/


/**
 *
 * 展示文件内容，可扩展接口
  *
*/
var ViewOper = {
	
	//文件展现形式
	textRender: function(content){
		$('#textDiv').html(content);
	},
	//iframe
	iframeRender: function(content){
	
	}
	
}

/**************************************************************/

/**
 *
 * 目录树类
 *
*/
var DirTree = {

	treeCache: [],//记录目录树是否加载
	
	treeObj: null,//树节点对象
	
	init: function(){
		var setting = {
			data: {
				simpleData: {
					enable: true
				}
			},
			callback: {
				onExpand: DirTree.zTreeOnExpand,
				onClick: DirTree.zTreeOnClick
				
			}
		};
		
		var zNodes =[
			{ id:1, pId:0, name:"\/", isParent: true, dirName: "/"}
		];
		this.treeObj = $.fn.zTree.init($("#treeId"), setting, zNodes);
		
	},
	/**
	* 展开节点事件
	*/
	zTreeOnExpand: function(event, treeId, treeNode){
		DirTree.reqNodeList(treeNode);
	},
	
	//点击节点事件
	zTreeOnClick: function(event, treeId, treeNode){
		if(treeNode.isParent) return;
		
		var param = treeNode.dirName.substring(0, treeNode.dirName.length - 1);
		DirTree.ajaxPostData(param, function(msg){				
			FileView.loadFile(treeNode.type, msg);
		});
	},
	
	/*
	* 对请求过来的节点进行封装
	*/
	renderNode: function(treeNode, nodes){
		var _newNodes = [];
		for(var i=0;i< nodes.length;i++){
			var name = nodes[i].name.replace(/\//g,'');	
			var node = { 
				id: treeNode.id + '_' + (i + 1),
				name: name,
				dirName: treeNode.dirName + name + '/',
				isParent: nodes[i].type.indexOf('/dir') > -1 ? true : false,
				pId : treeNode.id,
				type: nodes[i].type
			}
			_newNodes.push(node);
		}
		this.treeObj.addNodes(treeNode, _newNodes);
	},
	
	/**
	* 获取目录节点
	*/
	reqNodeList: function(treeNode){
		if(DirTree.treeCache[treeNode.id]){
			return;
		}
		var url = (treeNode && treeNode.dirName) || '';
		
		DirTree.ajaxPostData(url, function(msg){
			DirTree.treeCache[treeNode.id] = true;
			var list = eval('(' + msg + ')');
			DirTree.renderNode(treeNode, list);
		});
	},
	ajaxPostData: function(param, callback){
		var _url = param ;
		$.ajax({
		   type: "get",
		   dataType: "text",
		   url: _url ,
		   data: "",
		   success: function(msg){
				callback(msg);
		   },
		   error: function(){
			alert('load data error!url:' + _url);
		   }
		});
	},
	resize: function(){
		var height = $(window).height();
		$('.treeDiv,.content').height(height - 12);
	}
}