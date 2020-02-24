$(document).ready(notifyViewer);

function notifyViewer()
{
    var evt = document.createEvent("Events");
    evt.initEvent("ReportShown", true, false);
    document.dispatchEvent(evt);
}
