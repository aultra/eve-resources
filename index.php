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
            
            if (!file_exists('last_updated') || (filemtime('last_updated') < (time()-3600))) {
                echo "<!-- Updating database -->";
                $resources->updateResources();
                touch('last_updated');
            } else {
                echo "<!-- Database last updated ".round((time()-filemtime('last_updated'))/60)." minutes ago. -->";
            }
            
            $resources->display();
        ?>
    </body>
</html>
