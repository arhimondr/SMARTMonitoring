/**
 * Created with IntelliJ IDEA.
 * User: andy
 * Date: 9/29/13
 * Time: 9:02 PM
 * To change this template use File | Settings | File Templates.
 */


$(function(){
    $.ajax({
        url: 'http://localhost:8080/status',
        dataType: 'jsonp',
        success: function(data){
            var diskInfo = new SMARTMonitoring.ServerInfo(data);
            //debugger;
        }
    });
});