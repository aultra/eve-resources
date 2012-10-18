<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Phoenix Legion Resources Calculator</title>
        <?php
            if (!file_exists('includes/class.EveOreDB.inc')) {
                die("class.EveOreDB.inc must be created from class.EveOreDB.inc prior to this software working.");
            }
            require_once('includes/class.Resources.inc');
            require_once('includes/class.EveOreDB.inc');
        ?>
    </head>
    <body>
        <?php
            $resources = new Resources();
            $resources->loadResources();
            
            $resources->display();
        ?>
    </body>
</html>
