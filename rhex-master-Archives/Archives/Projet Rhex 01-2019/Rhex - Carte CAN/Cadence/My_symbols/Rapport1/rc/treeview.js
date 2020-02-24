$(document).ready(eventManager);
document.finder = null;

function browserSpecificObj()
{
    try
    {
        this.notifyViewer = function(){}            // stub - needed only in the diff3rptViewer
        
	    if(navigator.appName == "Microsoft Internet Explorer")
	    {
		    this.setEvents = function()
		    {
			    $("a").click(function(e)
			    {
				    location = $(this).attr('href');
				    handleHashChange();
			    });
		    }
		    this.openSummary = handleHashChange;
		    this.getHeight = function()
		    { return($("body").height() - 50); }
	    }
	    else
	    {
	        this.setEvents = function ()
	        {
	            $("a").click(function (e)
	            {
	                if ($(this).attr('href').substring(0, 7) == "file://")
	                {
	                    window.open($(this).attr('href'), '_blank', 'menubar=0,scrollbars=1');
	                    return false;
	                }
	            });
	        }
		    this.openSummary = function(){}
		    this.getHeight = function()
		    { return(window.innerHeight - 20); }
		    if (("buildID" in navigator) && (navigator.buildID == "diff3rptViewer"))
		    {
		        this.notifyViewer = function ()
		        {
		            var evt = document.createEvent("Events");
		            evt.initEvent("NavigationOccurredEvent", true, false);
		            document.dispatchEvent(evt);
		        }

		        document.addEventListener("FilterChangedEvent", OnFilterSettingChanged, true, true);
		        document.addEventListener("FindRequest", OnFind, true, true);
		        document.addEventListener("ExpandAll", OnExpandAll, true, true);
		        document.addEventListener("CollapseAll", OnCollapseAll, true, true);
		    }
	    }
	}
	catch(err)
	{alert(err);}
}

var browserSpecific = new browserSpecificObj();

window.onresize = fixMainframe;
// set up go to anchor handlers
if ("onhashchange" in window)  // event supported?
    window.onhashchange = handleHashChange;
else
{ // event not supported:
    var storedHash = window.location.hash;
    window.setInterval(
		function () {
		    if (window.location.hash != storedHash) {
		        storedHash = window.location.hash;
		        handleHashChange();
		    }
		}, 100);
}


function eventManager(e)
{
	fixMainframe();
	handleHashChange();
	
	// tree view management
	$(".treeview li").click(handleSelect);
	$("div.hitarea").click(handleExpandCollapse);
	
	browserSpecific.setEvents();

	// resizing mamangement
	var resizing = null;

	$("td.vsplitter").mousedown(function(e) 
	{
		resizing = new splitterObj($(this), true, e.pageX);
	});
	
	$("td.hsplitter").mousedown(function(e) 
	{
		resizing = new splitterObj($(this), false, e.pageY);
	});
	
	$(document).mousemove(function(e)
	{
		if(resizing != null)
		{
			resizing.resize(e.pageX, e.pageY);
		}
	});
	
	$(document).mouseup(function() {
		if(resizing != null) 
			resizing = null;
	});
}

function splitterObj(splitter, vertical, coord)
{
	var paneID = splitter.attr("ppane");
	this.ppane = $("#" + paneID);
	this.pcontent = $("#" + paneID + " div.paneCont");
	paneID = splitter.attr("npane");
	this.npane = $("#" + paneID);
	this.ncontent = $("#" + paneID + " div.paneCont");
	if(vertical)
	{
		this.PstartSize = this.ppane.width();
		this.NstartSize = this.npane.width();
	}
	else
	{
		this.PstartSize = this.ppane.height();
		this.NstartSize = this.npane.height();
	}
	this.start = coord;
	this.vertical = vertical;
	
	this.resize = function(X, Y)
	{
		if(this.vertical)
		{
			var delta = X - this.start;
			this.pcontent.width(this.PstartSize + delta);
			this.ppane.width(this.PstartSize + delta);
			this.ncontent.width(this.NstartSize - delta);
			this.npane.width(this.NstartSize - delta);
		}
		else
		{
			var delta = Y - this.start;
			this.pcontent.height(this.PstartSize + delta);
			this.ppane.height(this.PstartSize + delta);
			this.ncontent.height(this.NstartSize - delta);
			this.npane.height(this.NstartSize - delta);
		}
	}
}

function OnExpandAll()
{
    var nodes = $("td#treeview li.collapsed");
    nodes.toggleClass("collapsed");
    nodes.toggleClass("expanded");
}

function OnCollapseAll()
{
    var nodes = $("td#treeview li.expanded");
    nodes.toggleClass("collapsed");
    nodes.toggleClass("expanded");
}

function handleExpandCollapse()
{
	var id = $(this).attr("id");
	id = id.replace("-hitarea", "");	
	doExpandCollapse(id);
	return(false);
}

function handleSelect()
{
	var id = $(this).attr("id");
	openSummary(id);
	selectTreeNode(id);
	return(false);
}

function doExpandCollapse(id)
{
    var parent = $("li#" + id);
    if (parent.length == 0)             // the case of summary-notes
        parent = $("div#" + id);
	parent.toggleClass("collapsed");
	parent.toggleClass("expanded");
}

/// <summary>makes sure the given node is visible by expanding all its parents</summary>
/// <param name="nameNode">the DOM element specifyint the span.treeViewName of the node in question</param>
function expandTreeNodesParents(nameNode)
{
    var ul = nameNode;		// for the first time ul is a span (name node), whose parent is li - anyways, they both have the same parent
    var li;
    do {
        li = ul.parentNode;
        if (li.className.search("collapsed") >= 0)
            doExpandCollapse(li.id);
        ul = li.parentNode;
    } while (ul.nodeName.toLowerCase() == "ul");
}

function selectTreeNode(id)
{
    if($("#treeview").length == 0)
        return;                 // no treeview - e.g. when no changes were found
	if(id.substring(0,1) != "#")
		id = "#" + id;
		
	$(".treeview span.selected").removeClass("selected");
	var TVnameNode = $("li" + id + ">span.treeItemName");
	TVnameNode.addClass("selected");
	expandTreeNodesParents(TVnameNode[0]);
}

function openSummary(id)
{
	location.hash = "#" + id;
	browserSpecific.openSummary();
}

function handleHashChange()
{
	if(location.hash.length == 0)
	{
		location.hash = "#main-summary";
	}
	
	$("div#hidden-cache").append($("td#details.pane div.paneCont").children());
	$("td#details.pane div.paneCont").append($("div#hidden-cache div" + location.hash + "-cache"));
	selectTreeNode(location.hash);
	
	browserSpecific.notifyViewer();
	applyFilter("td#details");                     // filter setting did not change => apply only to details pane - leave treeveiw alone

	//alert("debugging");
	//OnFind();
	if (document.finder)
	    document.finder.ApplyToPage();
}

function fixMainframe()
{
	var H = browserSpecific.getHeight();
	$("tr#mainRow div.paneCont").height(H);
	$("tr#mainRow").height(H);
}

function FinderObj()
{
    this.str = "";
    this.ignoreCase = true;
    this.found = new Array();
    this.currentNdx = -1;

    // finds the nodes containing the text within the scope
    this.FindNodes = function(scope, rx)
    {
        var strsToFind = [];
        if (this.ignoreCase)
        {
            var matches = scope.text().match(rx);
            if (matches == null)
                return $();
            for (var i = 0; i < matches.length; i++)
            {
                if (strsToFind.indexOf(matches[i]) == -1)         // not in the array
                    strsToFind.push(matches[i]);
            }
        }
        else
            strsToFind.push(this.str);

        var nodes = $();
        for (var i = 0; i < strsToFind.length; i++)
            nodes = nodes.add(scope.find(":contains(" + strsToFind[i] + ")"));

        // we need only the leaf nodes, but the :contains() query returns all parents as well.
        for (var i = 1; i < nodes.length; i++)                      // do not cache length - it changes; do not process very first element, because nodes are sorted in parent->child order and we need the leaf node => the very first one would be a leaf as well
            nodes = nodes.not($(nodes[nodes.length - i]).parents());

        return nodes;
    }

    this.OnFind = function()
    {
        if(this.found.length > 0)   
            $(".found").removeClass("found");       // clear previous results

        var mf = $("#main-frame");
        this.str = mf.attr("string-to-find");
        this.found = [];                            // empty the list of IDs
        if (this.str.length > 0)
        {
            this.ignoreCase = (mf.attr("case-sensitive-find") == "false");
            if (this.ignoreCase)
                this.str = this.str.toLowerCase();

            var scope = $("#hidden-cache");
            // would be faster to search a lowercase copy - anyway, we need only ids - not the actual elements - so to find copies is good enough
            if (this.ignoreCase)
                var scope = $("<div>" + scope.html().toLowerCase() + "</div>");

            var divs = scope.find("div[id$='-cache']:contains(" + this.str + ")");

            var nDivs = divs.length;
            for (var i = 0; i < nDivs; i++)
            {
                var id = divs[i].id.replace("-cache", "");
                var treeItemName = $("td#treeview #" + id + ">span.treeItemName");
                this.found.push({ "id": id, "sortNdx": treeItemName.parent().attr("ndx") });
                treeItemName.addClass("found");
                expandTreeNodesParents(treeItemName[0]);
            }

            this.found.sort(function (a, b)
            {
                var aa = a.sortNdx.split(".");
                var bb = b.sortNdx.split(".");
                for(var i = 1; i < aa.length && i < bb.length; i++)     // start from 1, because 0 element is ""
                {
                    if (aa[i] != bb[i])
                        return aa[i] - bb[i];
                }
                return aa.length - bb.length;
            });
        }
        mf.attr("find-match-number", this.found.length.toString())
        this.ApplyToPage();

        var evt = document.createEvent("Events");
        evt.initEvent("FindDone", true, false);
        document.dispatchEvent(evt);
    }

    this.ApplyToPage = function()
    {
        var pane = $("td#details");

        // 1) remove previous find results
        var prev = pane.find("span.generatedbyfind");
        var len = prev.length;
        for (var i = 0; i < len; i++)
        {
            var to = prev[i].textContent;
            var from = "<span class=\"" + prev[i].className + "\">" + to + "</span>"; // outerHTML can be undefined;
            prev[i].parentNode.innerHTML = prev[i].parentNode.innerHTML.replace(from, to);
        }

        if (this.str.length == 0)
            return;

        var modifiers = "g";
        if (this.ignoreCase)
            modifiers += "i";

        // 2) apply new find
        var rx = new RegExp(this.str, modifiers);
        var nodes = this.FindNodes(pane, rx);

        len = nodes.length;
        for (var i = 0; i < len; i++)
        {
            if (nodes[i].innerHTML.match(rx).length == nodes[i].textContent.match(rx).length)   // make sure all the matches are in the text content
            {
                nodes[i].innerHTML = nodes[i].innerHTML.replace(rx, function (str)
                { return "<span class=\"found generatedbyfind\">" + str + "</span>"; }
                );
                var nonScalar = $(nodes[i]).parents().filter(".nonScalarDiff");
                if(nonScalar.length > 0)
                {
                    nonScalar.removeClass(PerLyrClsNames.D);
                    if (nodes[i].tagName.toLowerCase() == "span")
                    {
                        nonScalar.addClass(PerLyrClsNames.S);
                        nonScalar.removeClass(PerLyrClsNames.A);
                    }
                    else
                    {
                        nonScalar.removeClass(PerLyrClsNames.S);
                        nonScalar.addClass(PerLyrClsNames.A);
                    }
                }
            }
            // otherwise, leave unmakred... - maybe somewhat of an overkill, but safer this way
        }
    }

    this.OnFindNext = function ()
    {
        if (++document.finder.currentNdx >= document.finder.found.length)
            document.finder.currentNdx = 0;
        openSummary(document.finder.found[document.finder.currentNdx].id);
        selectTreeNode(document.finder.found[document.finder.currentNdx].id);
    }

    this.OnFindPrevious = function ()
    {
        if (--document.finder.currentNdx < 0)
            document.finder.currentNdx = document.finder.found.length-1;
        openSummary(document.finder.found[document.finder.currentNdx].id);
        selectTreeNode(document.finder.found[document.finder.currentNdx].id);
    }

    document.addEventListener("FindNext", this.OnFindNext, true, true);
    document.addEventListener("FindPrevious", this.OnFindPrevious, true, true);
}

function OnFind()
{
    if (document.finder == null)
        document.finder = new FinderObj();

    document.finder.OnFind();
}

