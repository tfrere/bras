import bpy, random, sys

max_dimensions = 730000;
current_dimensions = int(sys.argv[-1]) * int(sys.argv[-2])

technique = sys.argv[-3]
courant = sys.argv[-4]

print(technique)
print(courant)

ratio = current_dimensions / max_dimensions * 5

bpy.ops.mesh.primitive_cube_add(location = (0, 0, 1))

#bpy.ops.mesh.primitive_cylinder_add(location = (0, 0, 1))
  
bpy.context.scene.cursor_location = bpy.context.active_object.location
bpy.context.scene.cursor_location.z = 1
bpy.ops.object.origin_set(type='ORIGIN_CURSOR')
    
bpy.context.active_object.scale.x = 1
bpy.context.active_object.scale.y = 1
bpy.context.active_object.scale.z = 2 + ratio

## Reset du scale ##
bpy.ops.object.transform_apply(scale=True)

bpy.ops.object.editmode_toggle()
bpy.ops.mesh.subdivide(number_cuts=3)
bpy.ops.mesh.select_random()
bpy.ops.object.editmode_toggle()
bpy.ops.object.modifier_add(type='DISPLACE')
bpy.context.object.modifiers["Displace"].strength = 1
texture = bpy.data.textures.new(name="MyClouds", type='CLOUDS')
bpy.context.active_object.modifiers['Displace'].texture = texture


bpy.ops.mesh.print3d_export()