from osv.modules import api

api.require("jemalloc")
default = api.run("/bulk")
